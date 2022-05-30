/*_______________Schedule class______________*/
#ifndef TRAFFICSCHEDULER_H
#define TRAFFICSCHEDULER_H

/***********Includes************/
#include <iostream>
#include <vector>
#include "Task.h"

/*_______________Schedule class______________*/
/***********Definitions************/
#define occupied true
#define unoccupied false

// Block definititions
#define BlockSE 0							//Block South East
#define BlockNE 1							//Block North East
#define BlockNW 2							//Block Nort West
#define BlockSW 3							//Block South West
/***********Class declaration************/
class TrafficScheduler
{
  public:
    // Constructor including FSM
  	void TrafficScheduler();
    // Destructor
  	void ~TrafficScheduler();
  
  	// Return Block states
  	bool fRtBlockState_SE();
  	bool fRtBlockState_NE();
  	bool fRtBlockState_SW();
  	bool fRtBlockState_NW();
  
  	std::vector<Task> fReleaseVehicle();																			
  	void fAddTaskToList(std::vector<Task> p_NewTaskPool);
  	bool fCheckIfBlocksAreReservable(int p_Road, int p_Direction);
  	void fReserveBlocks(int p_Road, int p_Direction);
  	void fUnreserveBlock(int p_Block);
  	
  private:  
  	// states of 4 Blocks 
  	bool v_BlockSE = unoccupied;
    bool v_BlockNE = unoccupied;
  	bool v_BlockNW = unoccupied;
  	bool v_BlockSW = unoccupied;
  	
  	//Task Lists
  	std::vector<Task> v_Rd_East_TasksList;
  	std::vector<Task> v_Rd_West_TasksList;
  	std::vector<Task> v_Rd_North_TasksList;
  	std::vector<Task> v_Rd_South_TasksList;
  
  	unsigned long long int v_NextTaskID = 0;
  	
};

#endif