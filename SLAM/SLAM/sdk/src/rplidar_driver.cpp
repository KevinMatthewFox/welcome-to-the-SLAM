/*
 * Copyright (c) 2014, RoboPeak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 *  RoboPeak LIDAR System
 *  Serial based RPlidar Driver
 *
 *  Copyright 2009 - 2014 RoboPeak Team
 *  http://www.robopeak.com
 * 
 */


#include "pch.h"
#include "sdk/include/rplidar.h"

#include "sdkcommon.h"
#include "hal/abs_rxtx.h"
#include "hal/thread.h"
#include "hal/locker.h"
#include "hal/event.h"
#include "rplidar_driver_serial.h"

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

namespace rp { namespace standalone{ namespace rplidar {


// Factory Impl
RPlidarDriver * RPlidarDriver::CreateDriver(_u32 drivertype)
{
    switch (drivertype) {
    case DRIVER_TYPE_SERIALPORT:
        return new RPlidarDriverSerialImpl();
    default:
        return NULL;
    }
}


void RPlidarDriver::DisposeDriver(RPlidarDriver * drv)
{
    delete drv;
}



// Serial Driver Impl

RPlidarDriverSerialImpl::RPlidarDriverSerialImpl() 
    : _isConnected(false)
    , _isScanning(false)
{
    _rxtx = rp::hal::serial_rxtx::CreateRxTx();
    _cached_scan_node_count = 0;
}

RPlidarDriverSerialImpl::~RPlidarDriverSerialImpl()
{
    // force disconnection
    disconnect();

    rp::hal::serial_rxtx::ReleaseRxTx(_rxtx);
}

u_result RPlidarDriverSerialImpl::connect(const char * port_path, _u32 baudrate, _u32 flag)
{
    rp::hal::AutoLocker l(_lock);
    if (isConnected()) return RESULT_ALREADY_DONE;

    if (!_rxtx) return RESULT_INSUFFICIENT_MEMORY;

    // establish the serial connection...
    if (!_rxtx->bind(port_path, baudrate)  ||  !_rxtx->open()) {
        return RESULT_INVALID_DATA;
    }

    _rxtx->flush(0);
    _isConnected = true;

    return RESULT_OK;
}

void RPlidarDriverSerialImpl::disconnect()
{
    if (!_isConnected) return ;
    stop();
    _rxtx->close();
}

bool RPlidarDriverSerialImpl::isConnected()
{
    return _isConnected;
}


u_result RPlidarDriverSerialImpl::reset(_u32 timeout)
{
    u_result ans;
    if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_RESET))) {
        return ans;
    }
    return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::getHealth(rplidar_response_device_health_t & healthinfo, _u32 timeout)
{
    u_result  ans;
    
    if (!isConnected()) return RESULT_OPERATION_FAIL;
    
    _disableDataGrabbing();

    {
        rp::hal::AutoLocker l(_lock);
        if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_GET_DEVICE_HEALTH))) {
            return ans;
        }

        rplidar_ans_header_t response_header;
        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != RPLIDAR_ANS_TYPE_DEVHEALTH) {
            return RESULT_INVALID_DATA;
        }

        _u32 header_size = (response_header.size_q30_subtype & RPLIDAR_ANS_HEADER_SIZE_MASK);
        if ( header_size < sizeof(rplidar_response_device_health_t)) {
            return RESULT_INVALID_DATA;
        }

        if (_rxtx->waitfordata(header_size, timeout) != rp::hal::serial_rxtx::ANS_OK) {
            return RESULT_OPERATION_TIMEOUT;
        }
        _rxtx->recvdata(reinterpret_cast<_u8 *>(&healthinfo), sizeof(healthinfo));
    }
    return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::getDeviceInfo(rplidar_response_device_info_t & info, _u32 timeout)
{
    u_result  ans;
    
    if (!isConnected()) return RESULT_OPERATION_FAIL;

    _disableDataGrabbing();

    {
        rp::hal::AutoLocker l(_lock);
        if (IS_FAIL(ans = _sendCommand(RPLIDAR_CMD_GET_DEVICE_INFO))) {
            return ans;
        }

        rplidar_ans_header_t response_header;
        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != RPLIDAR_ANS_TYPE_DEVINFO) {
            return RESULT_INVALID_DATA;
        }

        _u32 header_size = (response_header.size_q30_subtype & RPLIDAR_ANS_HEADER_SIZE_MASK);
        if (header_size < sizeof(rplidar_response_device_info_t)) {
            return RESULT_INVALID_DATA;
        }

        if (_rxtx->waitfordata(header_size, timeout) != rp::hal::serial_rxtx::ANS_OK) {
            return RESULT_OPERATION_TIMEOUT;
        }

        _rxtx->recvdata(reinterpret_cast<_u8 *>(&info), sizeof(info));
    }
    return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::getFrequency(rplidar_response_measurement_node_t * nodebuffer, size_t count, float & frequency)
{
    const float RPLIDAR_SAMPLE_DURATION = 490.3; //ms
	if (count == 0)
	{
		frequency = 0.0f;
	}
	else
	{
		frequency = (float)(1000000/(count * RPLIDAR_SAMPLE_DURATION));
	}
	return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::startScan(bool force, _u32 timeout)
{
    u_result ans;
    if (!isConnected()) return RESULT_OPERATION_FAIL;
    if (_isScanning) return RESULT_ALREADY_DONE;

    stop(); //force the previous operation to stop

    {
        rp::hal::AutoLocker l(_lock);

        if (IS_FAIL(ans = _sendCommand(force?RPLIDAR_CMD_FORCE_SCAN:RPLIDAR_CMD_SCAN))) {
            return ans;
        }

        // waiting for confirmation
        rplidar_ans_header_t response_header;
        if (IS_FAIL(ans = _waitResponseHeader(&response_header, timeout))) {
            return ans;
        }

        // verify whether we got a correct header
        if (response_header.type != RPLIDAR_ANS_TYPE_MEASUREMENT) {
            return RESULT_INVALID_DATA;
        }

        _u32 header_size = (response_header.size_q30_subtype & RPLIDAR_ANS_HEADER_SIZE_MASK);
        if (header_size < sizeof(rplidar_response_measurement_node_t)) {
            return RESULT_INVALID_DATA;
        }

        _isScanning = true;
        _cachethread = CLASS_THREAD(RPlidarDriverSerialImpl, _cacheScanData);
    }
    return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::stop(_u32 timeout)
{
    _disableDataGrabbing();
    u_result ans = _sendCommand(RPLIDAR_CMD_STOP);
    return ans;
}

u_result RPlidarDriverSerialImpl::_cacheScanData()
{
    rplidar_response_measurement_node_t      local_buf[128];
    size_t                                   count = 128;
    rplidar_response_measurement_node_t      local_scan[MAX_SCAN_NODES];
    size_t                                   scan_count = 0;
    u_result                                 ans;
    memset(local_scan, 0, sizeof(local_scan));

    _waitScanData(local_buf, count); // // always discard the first data since it may be incomplete

    while(_isScanning)
    {
        if (IS_FAIL(ans=_waitScanData(local_buf, count))) {
            if (ans != RESULT_OPERATION_TIMEOUT) {
                _isScanning = false;
                return RESULT_OPERATION_FAIL;
            }
        }

        for (size_t pos = 0; pos < count; ++pos)
        {
            if (local_buf[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT)
            {
                // only publish the data when it contains a full 360 degree scan 
                
                if ((local_scan[0].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT)) {
                    _lock.lock();
                    memcpy(_cached_scan_node_buf, local_scan, scan_count*sizeof(rplidar_response_measurement_node_t));
                    _cached_scan_node_count = scan_count;
                    _dataEvt.set();
                    _lock.unlock();
                }
                scan_count = 0;
            }
            local_scan[scan_count++] = local_buf[pos];
            if (scan_count == _countof(local_scan)) scan_count-=1; // prevent overflow
        }
    }
    _isScanning = false;
    return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::grabScanData(rplidar_response_measurement_node_t * nodebuffer, size_t & count, _u32 timeout)
{
    switch (_dataEvt.wait(timeout))
    {
    case rp::hal::Event::EVENT_TIMEOUT:
        count = 0;
        return RESULT_OPERATION_TIMEOUT;
    case rp::hal::Event::EVENT_OK:
        {
            if(_cached_scan_node_count == 0) return RESULT_OPERATION_TIMEOUT; //consider as timeout

            rp::hal::AutoLocker l(_lock);

            size_t size_to_copy = min(count, _cached_scan_node_count);

            memcpy(nodebuffer, _cached_scan_node_buf, size_to_copy*sizeof(rplidar_response_measurement_node_t));
            count = size_to_copy;
            _cached_scan_node_count = 0;
        }
        return RESULT_OK;

    default:
        count = 0;
        return RESULT_OPERATION_FAIL;
    }
}

u_result RPlidarDriverSerialImpl::ascendScanData(rplidar_response_measurement_node_t * nodebuffer, size_t count)
{
    float inc_origin_angle = 360.0/count;
    int i = 0;

    //Tune head
    for (i = 0; i < count; i++) {
        if(nodebuffer[i].distance_q2 == 0) {
            continue;
        } else {
            while(i != 0) {
                i--;
                float expect_angle = (nodebuffer[i+1].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f - inc_origin_angle;
                if (expect_angle < 0.0f) expect_angle = 0.0f;
                _u16 checkbit = nodebuffer[i].angle_q6_checkbit & RPLIDAR_RESP_MEASUREMENT_CHECKBIT;
                nodebuffer[i].angle_q6_checkbit = (((_u16)(expect_angle * 64.0f)) << RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) + checkbit;
            }
            break;
        }
    }

    // all the data is invalid
    if (i == count) return RESULT_OPERATION_FAIL;

    //Tune tail
    for (i = count - 1; i >= 0; i--) {
        if(nodebuffer[i].distance_q2 == 0) {
            continue;
        } else {
            while(i != (count - 1)) {
                i++;
                float expect_angle = (nodebuffer[i-1].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f + inc_origin_angle;
                if (expect_angle > 360.0f) expect_angle -= 360.0f;
                _u16 checkbit = nodebuffer[i].angle_q6_checkbit & RPLIDAR_RESP_MEASUREMENT_CHECKBIT;
                nodebuffer[i].angle_q6_checkbit = (((_u16)(expect_angle * 64.0f)) << RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) + checkbit;
            }
            break;
        }
    }

    //Fill invalid angle in the scan
    float frontAngle = (nodebuffer[0].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;
    for (i = 1; i < count; i++) {
        if(nodebuffer[i].distance_q2 == 0) {
            float expect_angle =  frontAngle + i * inc_origin_angle;
            if (expect_angle > 360.0f) expect_angle -= 360.0f;
            _u16 checkbit = nodebuffer[i].angle_q6_checkbit & RPLIDAR_RESP_MEASUREMENT_CHECKBIT;
            nodebuffer[i].angle_q6_checkbit = (((_u16)(expect_angle * 64.0f)) << RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) + checkbit;
        }
    }

    // Reorder the scan according to the angle value
    for (i = 0; i < (count-1); i++){
        for (int j = (i+1); j < count; j++){
            if(nodebuffer[i].angle_q6_checkbit > nodebuffer[j].angle_q6_checkbit){
                rplidar_response_measurement_node_t temp = nodebuffer[i];
                nodebuffer[i] = nodebuffer[j];
                nodebuffer[j] = temp;
            }
        }
    }

    return RESULT_OK;
}

u_result RPlidarDriverSerialImpl::_waitNode(rplidar_response_measurement_node_t * node, _u32 timeout)
{
    int  recvPos = 0;
    _u32 startTs = getms();
    _u8  recvBuffer[sizeof(rplidar_response_measurement_node_t)];
    _u8 *nodeBuffer = (_u8*)node;
    _u32 waitTime;

   while ((waitTime=getms() - startTs) <= timeout) {
        size_t remainSize = sizeof(rplidar_response_measurement_node_t) - recvPos;
        size_t recvSize;

        int ans = _rxtx->waitfordata(remainSize, timeout-waitTime, &recvSize);
        if (ans == rp::hal::serial_rxtx::ANS_DEV_ERR) 
            return RESULT_OPERATION_FAIL;
        else if (ans == rp::hal::serial_rxtx::ANS_TIMEOUT)
            return RESULT_OPERATION_TIMEOUT;

        if (recvSize > remainSize) recvSize = remainSize;
        
        _rxtx->recvdata(recvBuffer, recvSize);

        for (size_t pos = 0; pos < recvSize; ++pos) {
            _u8 currentByte = recvBuffer[pos];
            switch (recvPos) {
            case 0: // expect the sync bit and its reverse in this byte
                {
                    _u8 tmp = (currentByte>>1);
                    if ( (tmp ^ currentByte) & 0x1 ) {
                        // pass
                    } else {
                        continue;
                    }

                }
                break;
            case 1: // expect the highest bit to be 1
                {
                    if (currentByte & RPLIDAR_RESP_MEASUREMENT_CHECKBIT) {
                        // pass
                    } else {
                        recvPos = 0;
                        continue;
                    }
                }
                break;
            }
            nodeBuffer[recvPos++] = currentByte;

            if (recvPos == sizeof(rplidar_response_measurement_node_t)) {
                return RESULT_OK;
            }
        }
    }

    return RESULT_OPERATION_TIMEOUT;
}

u_result RPlidarDriverSerialImpl::_waitScanData(rplidar_response_measurement_node_t * nodebuffer, size_t & count, _u32 timeout)
{
    if (!_isConnected) {
        count = 0;
        return RESULT_OPERATION_FAIL;
    }

    size_t   recvNodeCount =  0;
    _u32     startTs = getms();
    _u32     waitTime;
    u_result ans;

    while ((waitTime = getms() - startTs) <= timeout && recvNodeCount < count) {
        rplidar_response_measurement_node_t node;
        if (IS_FAIL(ans = _waitNode(&node, timeout - waitTime))) {
            return ans;
        }
        
        nodebuffer[recvNodeCount++] = node;

        if (recvNodeCount == count) return RESULT_OK;
    }
    count = recvNodeCount;
    return RESULT_OPERATION_TIMEOUT;
}

u_result RPlidarDriverSerialImpl::_sendCommand(_u8 cmd, const void * payload, size_t payloadsize)
{
    _u8 pkt_header[10];
    rplidar_cmd_packet_t * header = reinterpret_cast<rplidar_cmd_packet_t * >(pkt_header);
    _u8 checksum = 0;

    if (!_isConnected) return RESULT_OPERATION_FAIL;

    if (payloadsize && payload) {
        cmd |= RPLIDAR_CMDFLAG_HAS_PAYLOAD;
    }

    header->syncByte = RPLIDAR_CMD_SYNC_BYTE;
    header->cmd_flag = cmd;

    // send header first
    _rxtx->senddata(pkt_header, 2) ;

    if (cmd & RPLIDAR_CMDFLAG_HAS_PAYLOAD) {
        checksum ^= RPLIDAR_CMD_SYNC_BYTE;
        checksum ^= cmd;
        checksum ^= (payloadsize & 0xFF);

        // calc checksum
        for (size_t pos = 0; pos < payloadsize; ++pos) {
            checksum ^= ((_u8 *)payload)[pos];
        }

        // send size
        _u8 sizebyte = payloadsize;
        _rxtx->senddata(&sizebyte, 1);

        // send payload
        _rxtx->senddata((const _u8 *)payload, sizebyte);

        // send checksum
        _rxtx->senddata(&checksum, 1);
    }

    return RESULT_OK;
}


u_result RPlidarDriverSerialImpl::_waitResponseHeader(rplidar_ans_header_t * header, _u32 timeout)
{
    int  recvPos = 0;
    _u32 startTs = getms();
    _u8  recvBuffer[sizeof(rplidar_ans_header_t)];
    _u8  *headerBuffer = reinterpret_cast<_u8 *>(header);
    _u32 waitTime;

    while ((waitTime=getms() - startTs) <= timeout) {
        size_t remainSize = sizeof(rplidar_ans_header_t) - recvPos;
        size_t recvSize;
        
        int ans = _rxtx->waitfordata(remainSize, timeout - waitTime, &recvSize);
        if (ans == rp::hal::serial_rxtx::ANS_DEV_ERR) 
            return RESULT_OPERATION_FAIL;
        else if (ans == rp::hal::serial_rxtx::ANS_TIMEOUT)
            return RESULT_OPERATION_TIMEOUT;
        
        if(recvSize > remainSize) recvSize = remainSize;
        
        _rxtx->recvdata(recvBuffer, recvSize);

        for (size_t pos = 0; pos < recvSize; ++pos) {
            _u8 currentByte = recvBuffer[pos];
            switch (recvPos) {
            case 0:
                if (currentByte != RPLIDAR_ANS_SYNC_BYTE1) {
                   continue;
                }
                
                break;
            case 1:
                if (currentByte != RPLIDAR_ANS_SYNC_BYTE2) {
                    recvPos = 0;
                    continue;
                }
                break;
            }
            headerBuffer[recvPos++] = currentByte;

            if (recvPos == sizeof(rplidar_ans_header_t)) {
                return RESULT_OK;
            }
        }
    }

    return RESULT_OPERATION_TIMEOUT;
}



void RPlidarDriverSerialImpl::_disableDataGrabbing()
{
    _isScanning = false;
    _cachethread.join();
}

}}}
