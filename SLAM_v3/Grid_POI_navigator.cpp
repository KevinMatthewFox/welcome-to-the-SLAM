//TESTING THE CODE PORTING

//Team 15017
//Ported by: Kevin Fox

#include <vector>
#include <cmath>

#define FALSE 0
#define TRUE 1
#define PI 3.14159265
#define UNITSIZE 457.2 //rover size in millimeters
#define FIELDSIZE 101 //assign INF values to grid points with obstacles
#define INSERTHERE -1
#define INF 1000000

using namespace std;
using namespace rp::standalone::rplidar;

void gridPOI(void)
{
	vector<float> xMap; //xmap=[];
	vector<float> yMap; //ymap=[];
	vector<int> xGridPoints; //xgrid_points=[];
	vector<int> yGridPoints; //ygrid_points=[];

	float mapOriginX = 0; //map_origin=[0,0];
	float mapOriginY = 0; //map_origin=[0,0];

	int gridOriginX = 0; //grid_origin=[0,0];
	int gridOriginY = 0; //grid_origin=[0,0];

	//map and grid offsets not used
	//distance threshold and places visited not used

	bool finished = FALSE;
	int pos = 0;
	double xCoor = 0;
	double yCoor = 0;
	vector<float> x;
	vector<float> y;
	xMap.resize(0);
	yMap.resize(0);
	xGridPoints.resize(0);
	yGridPoints.resize(0);
	x.resize(1, -1);
	y.resize(1, -1);

	rplidar_response_measurement_node_t nodes[360 * 2]; //response packets
	size_t   count = _countof(nodes);

	while (!finished)
	{
		op_result = drv->grabScanData(nodes, count); //gets scan data from rplidar

		if (IS_OK(op_result))
		{
			drv->ascendScanData(nodes, count); //organizes scan data

			nodes[pos].angle_q6_checkbit = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f; //THETA in degrees
			nodes[pos].distance_q2 = nodes[pos].distance_q2 / 4.0f; //DISTANCE IN MILLIMETERS

			xCoor = nodes[pos].distance_q2 * cos(nodes[pos].angle_q6_checkbit * PI / 180.0); //convert to rectangular coordinate from polar
			yCoor = nodes[pos].distance_q2 * sin(nodes[pos].angle_q6_checkbit * PI / 180.0);

			x.front() = xCoor; //copy first x coordinate into x vector
			y.front() = yCoor; //copy first y coordinate into y vector

			for (pos = 1; pos < (int)count; ++pos) //copy response packets into x and y vectors
			{	
				nodes[pos].angle_q6_checkbit = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f; //THETA in degrees
				nodes[pos].distance_q2 = nodes[pos].distance_q2 / 4.0f; //DISTANCE IN MILLIMETERS
				//nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);

				xCoor = nodes[pos].distance_q2 * cos( nodes[pos].angle_q6_checkbit * PI / 180.0 ); //convert to rectangular coordinate from polar - x coordinate
				yCoor = nodes[pos].distance_q2 * sin( nodes[pos].angle_q6_checkbit * PI / 180.0 ); //convert to rectangular coordinate from polar - y coordinate

				x.push_back(xCoor); //add to end of x vector
				y.push_back(yCoor); //add to end of y vector
			}

			for (pos = 0; pos < (int)count; ++pos) //create xAdjusted
			{
				x.at(pos) += mapOriginX;
				y.at(pos) += mapOriginY;
			}
			//concatenation: vector1.insert( vector1.end(), vector2.begin(), vector2.end() );
			xMap.insert(xMap.end(), x.begin(), x.end()); //xmap=vertcat(xmap,x_adjusted); 
			yMap.insert(yMap.end(), y.begin(), y.end()); //ymap=vertcat(ymap,y_adjusted);

			vector<int> xNav;
			vector<int> yNav;
			xNav.resize(0); //x_nav1=ceil((xmap./unit_size));
			yNav.resize(0);

			for (pos = 0; pos < (int)count; ++pos) //create xNav, yNav
			{
				xNav.push_back(x.at(pos) / UNITSIZE); //x_nav1=ceil((xmap./unit_size));
				yNav.push_back(y.at(pos) / UNITSIZE); //y_nav1=ceil((ymap./unit_size));
			}

			xGridPoints.insert(xGridPoints.end(), xNav.begin(), xNav.end()); //xgrid_points=[xgrid_points;xnav_adjusted];
			yGridPoints.insert(yGridPoints.end(), yNav.begin(), yNav.end()); //ygrid_points=[ygrid_points;ynav_adjusted];

			//FIND GRID POIs for navigation
			bool field[FIELDSIZE][FIELDSIZE];
			int row = 0;
			int col = 0;
			for (row = 0; row < FIELDSIZE; row++)
			{
				for (col = 0; col < FIELDSIZE; col++)
				{
					field[row][col] = 1; //initialize to 1
				}
			}

			for (pos = 0; pos < xGridPoints.size(); ++pos)
			{
				field[-yGridPoints.at(pos) + (FIELDSIZE / 2)][-yGridPoints.at(pos) + (FIELDSIZE / 2)] = 0;
			}

			vector<int> xPOI;
			vector<int> yPOI;
			xPOI.resize(0);
			yPOI.resize(0);

			int count = 0;
			for (row = 0; row < FIELDSIZE; row++) //iterate through rows
			{
				for (col = 0; col < FIELDSIZE; col++)
				{
					count = 0;
					if (field[row][col] == 0) //check all neighbors
					{
						if (field[row + 1][col] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row + 1][col + 1] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row + 1][col - 1] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row][col + 1] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row][col - 1] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row - 1][col] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row - 1][col + 1] == 0)
						{
							count++;
						}
						else
						{
						}
						if (field[row - 1][col - 1] == 0)
						{
							count++;
						}
						else
						{
						}

						if (count == 1) //if exactly one neighbor is special
						{
							xPOI.push_back(col); //POIs=[POIs;[n q]];
							yPOI.push_back(row); //POIs=[POIs;[n q]];
						}
						else
						{
						}
					}
					else
					{
					}
				}
			}
			if (xPOI.empty()) //if isempty(POIs)
			{
				xPOI.resize(1, 0);
				yPOI.resize(1, 0);
			}
			else
			{
				for (pos = 0; pos < xPOI.size(); ++pos) //POIs=POIs-ceil(field_size/2);
				{
					xPOI.at(pos) -= (FIELDSIZE / 2);
					yPOI.at(pos) -= (FIELDSIZE / 2);
				}
			}

			//find midpoint between consecutive POI's
			vector<int> midpointX;
			vector<int> midpointY;
			midpointX.resize(xPOI.size(), 0); //midpointx=zeros(length(POI_x),1);
			midpointY.resize(yPOI.size(), 0); //midpointy=zeros(length(POI_y),1);
			if (xPOI.size() > 2)
			{
				for (pos = 0; pos < (xPOI.size() - 1); ++pos)
				{
					if (sqrt(pow((xPOI.at(pos) - xPOI.at(pos + 1)), 2) + pow((yPOI.at(pos) - yPOI.at(pos + 1)), 2)) > 6)
					{
						midpointX.at(pos) = 0; //midpointx(n)=0;
						midpointX.at(pos) = 0; //midpointy(n)=0;
					}
					else
					{
						midpointX.at(pos) = ((xPOI.at(pos) + xPOI.at(pos + 1)) / 2); //midpointx(n)=mean([POI_x(n),POI_x(n+1)]);
						midpointY.at(pos) = ((yPOI.at(pos) + yPOI.at(pos + 1)) / 2); //midpointy(n)=mean([POI_y(n),POI_y(n+1)]);
					}
				}
				if (sqrt(pow((xPOI.front() - xPOI.back()), 2) + pow((yPOI.front() - yPOI.back()), 2)) > 6)//if sqrt((POI_x(1) - POI_x(end)). ^ 2 + (POI_y(1) - POI_y(end)). ^ 2)>10
				{
					midpointX.back() = 0;//midpointx(length(POI_x)) = 0;
					midpointY.back() = 0;//midpointy(length(POI_x)) = 0;
				}
				else //else
				{
					midpointX.back() = ((xPOI.back() + xPOI.front()) / 2);//midpointx(length(POI_x)) = mean([POI_x(length(POI_x)), POI_x(1)]);
					midpointY.back() = ((yPOI.back() + yPOI.front()) / 2);//midpointy(length(POI_y)) = mean([POI_y(length(POI_y)), POI_y(1)]);
				}
			}
			else
			{
				if (xPOI.size() == 2)
				{
					midpointX.resize(1, ((xPOI.front() - xPOI.back()) / 2));//midpointx = mean(POI_x);
					midpointY.resize(1, ((yPOI.front() - yPOI.back()) / 2));//midpointy = mean(POI_y);
				}
				else //xPOI.size() == 1 [will always be at least 1, not 0]
				{
					midpointX.push_back(xPOI.front());
					midpointY.push_back(yPOI.front());
				}
			}
			
			//Pick travel points on grid
			vector<float> dist;//dist=zeros(length(midpointx),1);
			dist.resize(midpointX.size(), 0);//dist=zeros(length(midpointx),1);
			for (pos = 0; pos < midpointX.size(); ++pos) //for q=1:length(midpointx)
			{
				dist.at(pos) = sqrt(pow(0 - midpointX.at(pos) , 2) + pow(midpointY.at(pos) , 2)); //dist(q)=sqrt((0-midpointx(q)).^2+(0-midpointy(q)).^2);
			}
			int travelMidpointX = 0;
			int travelMidpointY = 0;

			int maxIndex = 0;
			for (pos = 1; pos < dist.size(); ++pos)
			{
				if (dist.at(pos) > dist.at(maxIndex))
				{
					maxIndex = pos;
				}
				else
				{
				}
			}
			travelMidpointX = midpointX.at(maxIndex); //Travel_midpoint=[round(midpointx(find(dist==max(dist)))),round(midpointy(find(dist==max(dist))))] ;
			travelMidpointY = midpointY.at(maxIndex); //Travel_midpoint=[round(midpointx(find(dist==max(dist)))),round(midpointy(find(dist==max(dist))))] ;
			//%%%this^ number is spit out in grid coordinates relative to origin;
			//%%%[-2, 5] means decrease two rows(go up) and move right 5 columns

			//path_to_travel = astaralgorithm(xgrid_points, ygrid_points, Travel_midpoint, grid_origin);
			
			////**** ASTAR ALGORITHM BEGIN ****////
			//function [p]=astaralgorithm(xgrid_points,ygrid_points,Travel_midpoint,grid_origin)

			////**** INITIALIZE FIELD BEGIN ****////
			//[field, startposind, goalposind, costchart, fieldpointers] = ...
				//initializeField(field_size, xgrid_points, ygrid_points, Travel_midpoint, grid_origin);
			unsigned char field2[FIELDSIZE][FIELDSIZE]; //field = ones(field_size,field_size);
			for (row = 0; row < FIELDSIZE; row++)
			{
				for (col = 0; col < FIELDSIZE; col++)
				{
					field2[row][col] = 1; //initialize to 1
				}
			}

			for (pos = 0; pos < xGridPoints.size(); ++pos) // for index=1:length(xgrid_points)
			{
				field2[yGridPoints.at(pos) + (FIELDSIZE / 2)][xGridPoints.at(pos) + (FIELDSIZE / 2)] = 2; // inf = 2; field(ygrid_points(index)+ceil(field_size/2),xgrid_points(index)+ceil(field_size/2)) = Inf;
			}

			//linearInd = sub2ind(matrixSize, rowSub, colSub) //row*cols+col;
			unsigned int startPosInd = (FIELDSIZE * (gridOriginX + (FIELDSIZE / 2))) + (gridOriginY + (FIELDSIZE / 2 ));//row = grid_origin(2)+ceil(field_size/2) // col = grid_origin(1)+ceil(field_size/2)
			//startposind = sub2ind( [field_size,field_size], grid_origin(2)+ceil(field_size/2), grid_origin(1)+ceil(field_size/2) ); %%%(0,0)
			unsigned int goalPosInd = (FIELDSIZE * (travelMidpointX + (FIELDSIZE / 2))) + (travelMidpointY + (FIELDSIZE / 2)); //row = Travel_midpoint(2) + ceil(field_size / 2) ; col = Travel_midpoint(1) + ceil(field_size / 2)
			//goalposind = sub2ind( [field_size, field_size], Travel_midpoint(2) + ceil(field_size / 2), Travel_midpoint(1) + ceil(field_size / 2) );   %%%Grided_Centroid
			//field(startposind) = 0; field(goalposind) = 0;
			unsigned int startPosIndRow = startPosInd % FIELDSIZE;
			unsigned int startPosIndCol = startPosInd / FIELDSIZE;
			unsigned int goalPosIndRow = goalPosInd % FIELDSIZE;
			unsigned int goalPosIndCol = goalPosInd / FIELDSIZE;
			field2[startPosIndRow][startPosIndCol] = 0; //C*FS + R
			field2[goalPosIndRow][goalPosIndCol] = 0; //   row=sub/cols; col = sub%cols;

			unsigned char fieldPointers[FIELDSIZE][FIELDSIZE]; //fieldpointers =0*ones(field_size,field_size);
			for (row = 0; row < FIELDSIZE; row++)
			{
				for (col = 0; col < FIELDSIZE; col++)
				{
					fieldPointers[row][col] = 5; //initialize to 0
				}
			}

			//fieldpointers(startposind) = 10; fieldpointers(goalposind) = 11;

			unsigned char fieldPointers[FIELDSIZE][FIELDSIZE]; //fieldpointers =0*ones(field_size,field_size);
			for (row = 0; row < FIELDSIZE; row++)
			{
				for (col = 0; col < FIELDSIZE; col++)
				{
					if (field2[row][col] == 2) //fieldpointers(field == Inf) = (0);
					{
						fieldPointers[row][col] = 0; 
					}
					else
					{
					}
				}
			}
			fieldPointers[startPosIndRow][startPosIndCol] = 10;
			fieldPointers[goalPosIndRow][goalPosIndCol] = 11;

			////**** INITIALIZE FIELD END ****////

			vector<unsigned int> setOpen;
			vector<unsigned int> setOpenCosts;
			vector<unsigned int> setOpenHeuristics;
			vector<unsigned int> setClosed;
			vector<unsigned int> setCLosedCosts;
			vector<unsigned int> movementDirections;

			setOpen.resize(1, startPosInd); //setOpen = [startposind];
			setOpenCosts.resize(1, 0); //setOpenCosts = [0];
			setOpenHeuristics.resize(1, 100000); //inf = 100,000 in this case
			setClosed.resize(0); //setClosed = [];
			setCLosedCosts.resize(0); // setClosedCosts = [];
			movementDirections.resize(4); //movementdirections = [1 2 3 4];%{'R','L','D','U'};
			movementDirections.at(0) = 1; //R
			movementDirections.at(1) = 2; //L
			movementDirections.at(2) = 3; //D
			movementDirections.at(3) = 4; //U

			int counterIterations = 1; //keep track of the number of iterations to exit gracefully if no solution

			//if goalposind is not in setopen, and setopen is not empty
			while (!setOpen.empty)	//THIS NEEDS UPDATE TO CHECK GOALPOSIND!!!!!!!!!!!!!!!!!!!!!!1
			{
				int temp = INSERTHERE ; // [temp, ii] = min(setOpenCosts + setOpenHeuristics);
				int ii = INSERTHERE ;

				////**** FIND F-VALUE BEGIN ****////
				//[costs, heuristics, posinds] = findFValue(setOpen(ii), setOpenCosts(ii), ...
				//	field, goalposind, 'euclidean');
				//function [cost,heuristic,posinds] = findFValue(posind,costsofar,field, ...
				//  goalind, heuristicmethod)

				//INITIALIZATIONS!
				unsigned int posInd = setOpen.at(ii);
				unsigned int costSoFar = setOpenCost.at(ii);
				unsigned int goalInd = goalPosInd;
				//field = field2 here
				int currentPos1 = 0; //currentpos = [ 0 0 ]
				int currentPos2 = 0;
				int goalPos1 = 0;
				int goalPos2 = 0;
				currentPos1 = INSERTHERE ; //[currentpos(1), currentpos(2)] = ind2sub([n n],posind);
				currentPos2 = INSERTHERE ; 
				goalPos1 = INSERTHERE ; //[goalpos(1), goalpos(2)] = ind2sub([n n],goalind);
				goalPos2 = INSERTHERE ; //[goalpos(1), goalpos(2)] = ind2sub([n n],goalind);
				vector<int> cost(4, INF); //cost = Inf*ones(4,1);
				vector<int> heuristic(4, INF); //heuristic = Inf*ones(4,1);
				vector<int> pos1(4, 1); //pos = ones(4,2);
				vector<int> pos2(4, 1); //pos = ones(4,2);
				////**** FIND F-VALUE END ****////
			}

			////**** ASTAR ALGORITHM END ****////
		} //if (IS_OK(op_result))
		else //else if (!IS_OK(op_result))
		{
		}
	} //while(!finished)

	return;
}

////**** FIND WAY BACK BEGIN****////
vector< vector<int> > findWayBack(unsigned int goalPosInd, unsigned int goalPosIndRow, unsigned int goalPosIndCol, unsigned char fieldPointers[FIELDSIZE][FIELDSIZE])
{
	//n = length(fieldpointers);  % length of the field
	unsigned int posInd = goalPosInd;//posind = goalposind;
	unsigned int posIndRow = goalPosIndRow;
	unsigned int posIndCol = goalPosIndCol;
	//% convert linear index into [row column]
	unsigned int py = goalPosIndRow; //[py, px] = ind2sub([n, n], posind);
	unsigned int px = goalPosIndCol;
	vector< vector<int> > p(1, vector<int>(2));
	p[0][0] = py;
	p[0][1] = px;
	

	//p = [py px];
	while (fieldPointers[goalPosIndRow][goalPosIndCol] != 10) //not start point
	{
		switch (fieldPointers[posIndRow][posIndCol])
		{
			case 2: //left
				px--;
				posInd = (FIELDSIZE * px) + py;
				posIndRow = posInd % FIELDSIZE;
				posIndCol = posInd / FIELDSIZE;
				p.resize(p.size() + 1);
				p[p.size() - 1][0] = py;
				p[p.size() - 1][1] = px;
				break;
			case 1: //right
				px++;
				posInd = (FIELDSIZE * px) + py;
				posIndRow = posInd % FIELDSIZE;
				posIndCol = posInd / FIELDSIZE;
				p.resize(p.size() + 1);
				p[p.size() - 1][0] = py;
				p[p.size() - 1][1] = px;
				break;
			case 4: //up
				py--;
				posInd = (FIELDSIZE * px) + py;
				posIndRow = posInd % FIELDSIZE;
				posIndCol = posInd / FIELDSIZE;
				p.resize(p.size() + 1);
				p[p.size() - 1][0] = py;
				p[p.size() - 1][1] = px;
				break;
			case 3: //down
				py++;
				posInd = (FIELDSIZE * px) + py;
				posIndRow = posInd % FIELDSIZE;
				posIndCol = posInd / FIELDSIZE;
				p.resize(p.size() + 1);
				p[p.size() - 1][0] = py;
				p[p.size() - 1][1] = px;
				break;
			default: //shake it all about
				break;
		/*
		//linearInd = sub2ind(matrixSize, rowSub, colSub) //row*cols+col;
		unsigned int startPosInd = (FIELDSIZE * (gridOriginX + (FIELDSIZE / 2))) + (gridOriginY + (FIELDSIZE / 2));//row = grid_origin(2)+ceil(field_size/2) // col = grid_origin(1)+ceil(field_size/2)
																													   //startposind = sub2ind( [field_size,field_size], grid_origin(2)+ceil(field_size/2), grid_origin(1)+ceil(field_size/2) ); %%%(0,0)
		unsigned int goalPosInd = (FIELDSIZE * (travelMidpointX + (FIELDSIZE / 2))) + (travelMidpointY + (FIELDSIZE / 2)); //row = Travel_midpoint(2) + ceil(field_size / 2) ; col = Travel_midpoint(1) + ceil(field_size / 2)
																																   //goalposind = sub2ind( [field_size, field_size], Travel_midpoint(2) + ceil(field_size / 2), Travel_midpoint(1) + ceil(field_size / 2) );   %%%Grided_Centroid
																																   //field(startposind) = 0; field(goalposind) = 0;
		unsigned int startPosIndRow = startPosInd % FIELDSIZE;
		unsigned int startPosIndCol = startPosInd / FIELDSIZE;
		*/
		}
	}
	return p;
}

////**** FIND WAY BACK END ****////



/*
typedef struct _rplidar_response_measurement_node_t {
_u8    sync_quality;      // syncbit:1;syncbit_inverse:1;quality:6;
_u16   angle_q6_checkbit; // check_bit:1;angle_q6:15; divide by 64.0
_u16   distance_q2; 
} __attribute__((packed)) rplidar_response_measurement_node_t;
*/