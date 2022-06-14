/*_______________Schedule class______________*/
#ifndef TRAFFICSCHEDULER_H
#define TRAFFICSCHEDULER_H

/***********Includes************/
#include "Task.h"

/***********Definitions************/
#define occupied true
#define unoccupied false

// Block definititions
#define BlockSE 0              //Block South East
#define BlockNE 1             //Block North East
#define BlockNW 2             //Block Nort West
#define BlockSW 3             //Block South West
/***********Class declaration************/
class TrafficScheduler
{
public:
  // Constructor including FSM
  TrafficScheduler();
  // Destructor
  ~TrafficScheduler();

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

  unsigned long v_Block_SECounter = 0;
  unsigned long v_Block_SWCounter = 0;
  unsigned long v_Block_NECounter = 0;
  unsigned long v_Block_NWCounter = 0;
  
  int v_Block_SEDirection = -1;
  int v_Block_SWDirection = -1;
  int v_Block_NEDirection = -1;
  int v_Block_NWDirection = -1;

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
