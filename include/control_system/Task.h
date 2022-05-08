/*_______________Task class______________*/
#ifndef TASK_H
#define TASK_H

/***********Includes************/
#include <iostream>

/***********Definitions************/
// Travel Direction
#define Straight 0
#define TurnLeft 1
#define TurnRight 2
// Roads definititions
#define MainRd_rLane 0
#define MainRd_lLane 1
#define SideRd_rLane 2
#define SideRd_lLane 3

/***********Class declaration************/
class Task
{
	public:
		// Constructor
		Task(int p_TaskID, int p_VehicleID, int p_Road, int p_Destination, int p_TravelDirection);
		// Destructor
		~Task();
		// Return functions
		int fRtTaskID();
		int fRtVehicleID();
		int fRtPriority();
		int fRtRoad();
		int fRtDestination();
		int fRtDirection();

	private:
		int v_TaskID;
		int v_VehicleID;
		int v_Road;
		int v_Destination;
		int v_TravelDirection;
};

#endif