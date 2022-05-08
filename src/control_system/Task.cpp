#include "control_system/Task.h"

/*_______________Task class functions______________*/
Task::Task(int p_TaskID, int p_VehicleID, int p_Road, int p_Destination, int p_TravelDirection)
{
	this->v_TaskID = p_TaskID;
	this->v_VehicleID = p_VehicleID;
	this->v_Road = p_Road;
	this->v_Destination = p_Destination;
	this->v_TravelDirection = p_TravelDirection;
}

Task::~Task()
{
	// TODO: Destructor - last to do
}

int Task::fRtTaskID()
{
	return this->v_TaskID;
}

int Task::fRtVehicleID()
{
	return this->v_VehicleID;
}

int Task::fRtRoad()
{
	return this->v_Road;
}

int Task::fRtDestination()
{
	return this->v_Destination;
}

int Task::fRtDirection()
{
	return this->v_TravelDirection;
}