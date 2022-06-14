/****************************************************************************
 * 													Kernel       																		*
 ****************************************************************************/

#include <iostream>
#include <control_system/TrafficScheduler.h>
#include <control_system/Task.h>

#define RoadEastWest 0
#define RoadNorthSouth 1
char Map[35][35];
int i, j;


void InitMap()
{
	for (i = 0; i < 35; i++)
		for (j = 0; j < 35; j++)
			Map[i][j] = ' ';

	for (j = 0; j < 15; j++)
	{
		Map[14][j] = '*';
		Map[14][j + 18] = '*';
		Map[16][j] = '*';
		Map[16][j + 18] = '*';
		Map[18][j] = '*';
		Map[18][j + 18] = '*';
	}

	for (i = 0; i < 15; i++)
	{
		Map[i][14] = '*';
		Map[i][18] = '*';
		Map[i][16] = '*';
		Map[i + 18][16] = '*';
		Map[i + 18][14] = '*';
		Map[i + 18][18] = '*';
	}

	for (i = 0; i < 35; i++)
	{
		for (j = 0; j < 35; j++)
		{
			std::cout << Map[i][j];
			std::cout << ' ';
		}
		std::cout << '\n';
	}
}



int main()
{
	int v_state = RoadNorthSouth;
	std::vector<Task> NewTaskPool;
	TrafficScheduler v_Scheduler;
	Task TestV1(1, Rd_South, Straight);
	NewTaskPool.push_back(TestV1);

	Task TestV2(2, Rd_East, TurnRight);
	NewTaskPool.push_back(TestV2);

	InitMap();
	v_Scheduler.fAddTaskToList(NewTaskPool);

	for (int i = 0; i < 2; i++)
	{
		

		if (i == 0)
		{
			std::cout << "Size of task list south: " << v_Scheduler.v_Rd_South_TasksList.size() << std::endl;
			std::cout << "Size of task list north: " << v_Scheduler.v_Rd_North_TasksList.size() << std::endl;
			std::cout << "Size of task list east: " << v_Scheduler.v_Rd_East_TasksList.size() << std::endl;
			std::cout << "Size of task list west: " << v_Scheduler.v_Rd_West_TasksList.size() << std::endl;

			std::cout << "Task 1 Vehicle ID: " << v_Scheduler.v_Rd_South_TasksList[i].fRtVehicleID() << std::endl;
			std::cout << "Task 1 Task ID: " << v_Scheduler.v_Rd_South_TasksList[i].fRtTaskID() << std::endl;
			std::cout << "Task 1 Road: " << v_Scheduler.v_Rd_South_TasksList[i].fRtRoad() << std::endl;
			std::cout << "Task 1 Direction: " << v_Scheduler.v_Rd_South_TasksList[i].fRtDirection() << std::endl;
			std::cout << "Task 1 Arrival Time: " << v_Scheduler.v_Rd_South_TasksList[i].fRtArrivalTime() << std::endl;

			std::cout << "Task 2 Vehicle ID: " << v_Scheduler.v_Rd_East_TasksList[i].fRtVehicleID() << std::endl;
			std::cout << "Task 2 Task ID: " << v_Scheduler.v_Rd_East_TasksList[i].fRtTaskID() << std::endl;
			std::cout << "Task 2 Road: " << v_Scheduler.v_Rd_East_TasksList[i].fRtRoad() << std::endl;
			std::cout << "Task 2 Direction: " << v_Scheduler.v_Rd_East_TasksList[i].fRtDirection() << std::endl;
			std::cout << "Task 2 Arrival Time: " << v_Scheduler.v_Rd_East_TasksList[i].fRtArrivalTime() << std::endl;

			v_Scheduler.fReleaseVehicle();
			
			if (v_Scheduler.fRtBlockState_NE() != occupied)
				std::cout << "ERROR! Task 2 was not released!" << std::endl;
			else
				std::cout <<  "Task 2 was released! Vehicle release is working fine!" << std::endl;
			//	Test code here
		}

		if (i == 1)
		{
			// Try releasing vehicle before the block is unreserved
			std::cout << "Size of task list south: " << v_Scheduler.v_Rd_South_TasksList.size() << std::endl;
			std::cout << "Size of task list north: " << v_Scheduler.v_Rd_North_TasksList.size() << std::endl;
			std::cout << "Size of task list east: " << v_Scheduler.v_Rd_East_TasksList.size() << std::endl;
			std::cout << "Size of task list west: " << v_Scheduler.v_Rd_West_TasksList.size() << std::endl;

			v_Scheduler.fReleaseVehicle();
			if (v_Scheduler.fRtBlockState_SE() == occupied)
				std::cout << "ERROR! The blocks was reserved even though there are occupied resources!" << std::endl;
			else
				std::cout << "Block checking is working fine!" << std::endl;
			
			// Unreserve block
			std::cout << "Unblocking the block" << std::endl;
			v_Scheduler.fUnreserveBlock(BlockNE);
			
			// Try releasing again!
			v_Scheduler.fReleaseVehicle();
			
			if (v_Scheduler.fRtBlockState_SE() != occupied || v_Scheduler.fRtBlockState_NE() != occupied)
				std::cout << "ERROR! Task 1 was not released!" << std::endl;
			else
				std::cout << "Task 1 was released! Vehicle release is working fine!" << std::endl;

		}



	}
	return 0;
}


