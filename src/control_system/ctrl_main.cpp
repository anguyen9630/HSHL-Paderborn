/****************************************************************************
 * 								Kernel										*       																		*
 ****************************************************************************/

#include <iostream>
#include <vector>
#include "control_system/TrafficScheduler.h"
#include "control_system/Task.h"

#define SideRd 0
#define MainRd 1

int main()
{
	int v_state = MainRd;
	std::vector<Task> NewTaskPool;
	TrafficScheduler v_Scheduler;
	std::cout << "Scheduler Initialized!" << std::endl;

	while (true)
	{
		int v_count = 0;
		/******************************/
		// TODO: Stimulus generation  //
		/******************************/
		v_Scheduler.fAddTaskToList(NewTaskPool);
		
		// State machine
		switch (v_state)
		{
		case MainRd:
			std::cout << "State Main Road!" << std::endl;
			if (v_Scheduler.fRtSizeOfMainRdRightList() == 0 or v_Scheduler.fRtSizeOfMainRdLeftList() == 0 or v_count == 2)
			{
				v_state = SideRd;
				v_count = 0;
			}
			else
			{
				v_Scheduler.fMainRoadReleaseSchedule();
				v_count++;
			}
			break;

		case SideRd:
			std::cout << "State Side Road!" << std::endl;
			if (v_Scheduler.fRtSizeOfSideRdRightList() == 0 or v_Scheduler.fRtSizeOfSideRdLeftList() == 0 or v_count == 2)
			{
				v_state = MainRd;
				v_count = 0;
			}
			else
			{
				v_Scheduler.fSideRoadReleaseSchedule();
				v_count++;
			}
			break;
		}
	}
	return 0;
}