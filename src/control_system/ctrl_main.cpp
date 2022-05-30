/****************************************************************************
 * 								Kernel										*       																		*
 ****************************************************************************/

#include <iostream>
#include <vector>
#include "control_system/TrafficScheduler.h"
#include "control_system/Task.h"

#define RoadEastWest 0
#define RoadNorthSouth 1

int main()
{
  v_state = RoadNorthSouth;
  std::vector<Task> NewTaskPool;
  TrafficScheduler v_Scheduler; 
  
  while(true)
  {
    int v_count = 0;
    /******************************/
    // TODO: Stimulus generation  //
    /******************************/
		v_Scheduler.fAddTaskToList(NewTaskPool);
  
  }
  return 0;
}
