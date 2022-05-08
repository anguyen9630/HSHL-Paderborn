#include "control_system/TrafficScheduler.h"

/*_______________Scheduler class functions______________*/
TrafficScheduler::TrafficScheduler()
{
	// Empty Contructor
}

TrafficScheduler::~TrafficScheduler()
{
	// Empty destructor
}

void TrafficScheduler::fMainRoadReleaseSchedule()
{
	if (this->v_MainRd_R_TasksList.size() > 0)
	{
		if (this->v_TopRight == unoccupied && this->v_BottomRight == unoccupied)
		{
			this->v_VehicleReleaseList.push_back(this->v_MainRd_R_TasksList.back());
			this->v_MainRd_R_TasksList.pop_back();
		}
	}
	if (this->v_MainRd_L_TasksList.size() > 0)
	{
		if (this->v_TopLeft == unoccupied && this->v_BottomLeft == unoccupied)
		{
			this->v_VehicleReleaseList.push_back(this->v_MainRd_L_TasksList.back());
			this->v_MainRd_R_TasksList.pop_back();
		}
	}
}

void TrafficScheduler::fSideRoadReleaseSchedule()
{
	if (this->v_SideRd_R_TasksList.size() > 0)
	{
		if (this->v_TopRight == unoccupied && this->v_TopLeft == unoccupied)
		{
			this->v_VehicleReleaseList.push_back(this->v_MainRd_R_TasksList.back());
			this->v_MainRd_R_TasksList.pop_back();
		}
	}
	if (this->v_SideRd_L_TasksList.size() > 0)
	{
		if (this->v_BottomRight == unoccupied && this->v_BottomLeft == unoccupied)
		{
			this->v_VehicleReleaseList.push_back(this->v_MainRd_L_TasksList.back());
			this->v_MainRd_R_TasksList.pop_back();
		}
	}
}


void TrafficScheduler::fAddTaskToList(std::vector<Task> p_NewTaskPool)
{
	for (int v_Indx = 0; v_Indx < p_NewTaskPool.size(); v_Indx++)
	{
		Task v_NewTask = p_NewTaskPool[v_Indx];

		switch (v_NewTask.fRtRoad())
		{
		case MainRd_rLane:
			this->v_MainRd_R_TasksList.insert(this->v_MainRd_R_TasksList.begin(), v_NewTask);
			break;
		case MainRd_lLane:
			this->v_MainRd_L_TasksList.insert(this->v_MainRd_L_TasksList.begin(), v_NewTask);
			break;
		case SideRd_rLane:
			this->v_SideRd_R_TasksList.insert(this->v_SideRd_R_TasksList.begin(), v_NewTask);
			break;
		case SideRd_lLane:
			this->v_SideRd_L_TasksList.insert(this->v_SideRd_L_TasksList.begin(), v_NewTask);
			break;
		}
	}
}

int TrafficScheduler::fRtSizeOfMainRdRightList()
{
	return this->v_MainRd_R_TasksList.size();
}
int TrafficScheduler::fRtSizeOfMainRdLeftList()
{
	return this->v_MainRd_L_TasksList.size();
}
int TrafficScheduler::fRtSizeOfSideRdRightList()
{
	return this->v_SideRd_R_TasksList.size();
}
int TrafficScheduler::fRtSizeOfSideRdLeftList()
{
	return this->v_SideRd_L_TasksList.size();
}