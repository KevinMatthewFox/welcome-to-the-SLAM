//
// File: new_serial_ex.h
// Author: Kevin Fox
//

#pragma once

#include <Windows.h>
#include <fileapi.h>
#include <WinBase.h>

#define WINBASEAPI DECLSPEC_IMPORT

WINBASEAPI
HANDLE
WINAPI
CreateFileA(
	_In_ LPCSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
	);

#define CreateFile  CreateFileA

WINBASEAPI
BOOL
WINAPI
SetupComm(
	_In_ HANDLE hFile,
	_In_ DWORD dwInQueue,
	_In_ DWORD dwOutQueue
	);

WINBASEAPI
BOOL
WINAPI
SetCommState(
	_In_ HANDLE hFile,
	_In_ LPDCB lpDCB
	);

WINBASEAPI
BOOL
WINAPI
EscapeCommFunction(
	_In_ HANDLE hFile,
	_In_ DWORD dwFunc
	);

WINBASEAPI
BOOL
WINAPI
SetCommTimeouts(
	_In_ HANDLE hFile,
	_In_ LPCOMMTIMEOUTS lpCommTimeouts
	);

WINBASEAPI
BOOL
WINAPI
SetCommMask(
	_In_ HANDLE hFile,
	_In_ DWORD dwEvtMask
	);

WINBASEAPI
BOOL
WINAPI
PurgeComm(
	_In_ HANDLE hFile,
	_In_ DWORD dwFlags
	);

WINBASEAPI
BOOL
WINAPI
ClearCommError(
	_In_      HANDLE hFile,
	_Out_opt_ LPDWORD lpErrors,
	_Out_opt_ LPCOMSTAT lpStat
	);

WINBASEAPI
BOOL
WINAPI
GetOverlappedResult(
	_In_ HANDLE hFile,
	_In_ LPOVERLAPPED lpOverlapped,
	_Out_ LPDWORD lpNumberOfBytesTransferred,
	_In_ BOOL bWait
	);

WINBASEAPI
BOOL
WINAPI
WaitCommEvent(
	_In_        HANDLE hFile,
	_Inout_     LPDWORD lpEvtMask,
	_Inout_opt_ LPOVERLAPPED lpOverlapped
	);
