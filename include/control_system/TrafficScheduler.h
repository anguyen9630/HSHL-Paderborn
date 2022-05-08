/*_______________Schedule class______________*/
#ifndef TRAFFICSCHEDULER_H
#define TRAFFICSCHEDULER_H

/***********Includes************/
#include <iostream>
#include <vector>
#include "Task.h"

/***********Definitions************/
#define state_Idle 0
#define state_Active 1

#define occupied true
#define unoccupied false
/***********Class declaration************/
class TrafficScheduler
{
	public:
		// Constructor including FSM
		TrafficScheduler();
		// Destructor
		~TrafficScheduler();

		int fRtSizeOfMainRdRightList();
		int fRtSizeOfMainRdLeftList();
		int fRtSizeOfSideRdRightList();
		int fRtSizeOfSideRdLeftList();

		void fMainRoadReleaseSchedule();
		void fSideRoadReleaseSchedule();
		void fAddTaskToList(std::vector<Task> p_NewTaskPool);
		std::vector<Task> v_VehicleReleaseList;

	private:
		int v_state = state_Idle;
		std::vector<Task> v_MainRd_R_TasksList;
		std::vector<Task> v_MainRd_L_TasksList;
		std::vector<Task> v_SideRd_R_TasksList;
		std::vector<Task> v_SideRd_L_TasksList;

		/*bool v_MainRd_rLane = unoccupied;
		bool v_MainRd_lLane = unoccupied;
		bool v_SideRd_rLane = unoccupied;
		bool v_SideRd_lLane = unoccupied;*/

		bool v_TopRight = unoccupied;
		bool v_TopLeft = unoccupied;
		bool v_BottomRight = unoccupied;
		bool v_BottomLeft = unoccupied;
};

#endif