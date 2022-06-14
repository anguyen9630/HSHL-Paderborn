#include "control_system/Task.h"

/*_______________Task class______________*/
Task::Task(int p_VehicleID, int p_Road, int p_Direction)
{
	this->v_VehicleID = p_VehicleID;
	this->v_Road = p_Road;
	this->v_Direction = p_Direction;
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

int Task::fRtDirection()
{
	return this->v_Direction;
}

std::clock_t Task::fRtArrivalTime()
{
	return this->v_TaskArrivalTime;
}

void Task::fAssignTaskID(int p_TaskID)
{
	this->v_TaskID = p_TaskID;
}

void Task::fAssignArrivalTime(std::clock_t p_Time)
{
	this->v_TaskArrivalTime = p_Time;
}
