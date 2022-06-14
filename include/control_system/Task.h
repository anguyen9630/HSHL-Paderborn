#ifndef TASK_H
#define TASK_H

#include <ctime>

/*_______________Task class______________*/
/***********Definitions************/
// Travel Direction (also include priority - lower the higher the priority)
#define TurnRight 0
#define Straight 1
#define TurnLeft 2

// Road definitions
#define Rd_East 0							//Road going from East side
#define Rd_West 1							//Road going from West side
#define Rd_North 2						//Road going from North side
#define Rd_South 3						//Road going from South side
/***********Class declaration************/
class Task
{
public:
	// Constructor
	Task(int p_VehicleID, int p_Road, int p_Direction);
	// Destructor
	~Task();
	// Return functions
	int fRtTaskID();
	int fRtVehicleID();
	int fRtRoad();
	int fRtDirection();
	std::clock_t fRtArrivalTime();
	// Assign functions
	void fAssignTaskID(int p_TaskID);
	void fAssignArrivalTime(std::clock_t p_Time);

private:
	// Initial values of -1 to indicate uninitialized/bad init
	int v_TaskID = -1;
	int v_VehicleID = -1;
	int v_Road = -1;
	int v_Direction = -1;
	std::clock_t v_TaskArrivalTime = -1;
};

#endif