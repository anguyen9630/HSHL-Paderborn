



void TrafficScheduler::~TrafficScheduler()
{
  // TODO: Scheduler destructor
}

/*
 * 
 *  NW  NE
 *  SW  SE
 * */

void TrafficScheduler::fReserveBlocks(int p_Road, int p_Direction)
{
  if (p_Road == Rd_East)
  {
    if (p_Direction == Straight)
    {
      //Reserve BlockNE && BlockNW
      this->v_BlockNE = occupied;
      this->v_BlockNW = occupied;
    }
    else if (p_Direction == TurnRight)
    {
      //Reserve BlockNE
      this->v_BlockNE = occupied;
    }
    else if(p_Direction == TurnLeft)
    {
      //Reserve BlockNE, NW, SW
      this->v_BlockNE = occupied;
      this->v_BlockNW = occupied;
      this->v_BlockSW = occupied;
    }
  }
  else if (p_Road == Rd_West)
  {
    if (p_Direction == Straight)
    {
      //Reserve BlockSW && BlockSE
      this->v_BlockSW = occupied;
      this->v_BlockSE = occupied;
    }
    else if (p_Direction == TurnRight)
    {
      //Reserve BlockSW
      this->v_BlockSW = occupied;
    }
    else if(p_Direction == TurnLeft)
    {
      //Reserve BlockSW, SE, NE
      this->v_BlockSW = occupied;
      this->v_BlockSE = occupied;
      this->v_BlockNE = occupied;
    }
  }
  else if (p_Road == Rd_North)
  {
    if (p_Direction == Straight)
    {
      //Reserve BlockNW && BlockSW
      this->v_BlockNW = occupied;
      this->v_BlockSW = occupied;
    }
    else if (p_Direction == TurnRight)
    {
      //Reserve BlockNW
      this->v_BlockNW = occupied;
    }
    else if(p_Direction == TurnLeft)
    {
      //Reserve BlockNW, SW, SE
      this->v_BlockNW = occupied;
      this->v_BlockSW = occupied;
      this->v_BlockSE = occupied;
    }
  }
  else if (p_Road == Rd_South)
  {
    if (p_Direction == Straight)
    {
      //Reserve BlockSE && BlockNE
      this->v_BlockSE = occupied;
      this->v_BlockNE = occupied;
    }
    else if (p_Direction == TurnRight)
    {
      //Reserve BlockSE
      this->v_BlockSE = occupied;
    }
    else if(p_Direction == TurnLeft)
    {
      //Reserve BlockSE, NE, NW
      this->v_BlockSE = occupied;
      this->v_BlockNE = occupied;
      this->v_BlockNW = occupied;
    }
  }
}

void TrafficScheduler::fUnreserveBlock(int p_Block)
{
  // Function to run reserve the block (Use when the car passes a certain point)
  switch(p_Block)
  {
    case BlockSE:
      this->v_BlockSE = unoccupied;
      break;
    case BlockSW:
      this->v_BlockSW = unoccupied;
      break;
    case BlockNE:
      this->v_BlockNE = unoccupied;
      break;
    case BlockNW:
      this->v_BlockNW = unoccupied;
      break;
  }
}


/*
 * 
 *  NW  NE
 *  SW  SE
 * */
bool TrafficScheduler::fCheckIfBlocksAreReservable(int p_Road, int p_Direction)
{
  switch(p_Road)
  {
    //If vehicle coming from East
    case Rd_East:
      //If vehicle goes straight 
      if(p_Direction == Straight && (this->v_BlockNE == occupied || this->v_BlockNW == occupied))
      	return false;
    	else if (p_Direction == TurnRight && (this->v_BlockNE == occupied))
        return false;
    	else if (p_Direction == TurnLeft && (this->v_BlockNE == occupied || this->v_BlockNW == occupied || this->v_BlockSW == occupied))
        return false;
      else return true;
      break;
    case Rd_West:
			if(p_Direction == Straight && (this->v_BlockSW == occupied || this->v_BlockSE == occupied))
      	return false;
    	else if (p_Direction == TurnRight && (this->v_BlockSW == occupied))
        return false;
    	else if (p_Direction == TurnLeft && (this->v_BlockSW == occupied || this->v_BlockSE == occupied || this->v_BlockNE == occupied))
        return false;
      else return true;
      break;
    case Rd_North:
      if(p_Direction == Straight && (this->v_BlockNW == occupied || this->v_BlockSW == occupied))
      	return false;
    	else if (p_Direction == TurnRight && (this->v_BlockNW == occupied))
        return false;
    	else if (p_Direction == TurnLeft && (this->v_BlockNW == occupied || this->v_BlockSW == occupied || this->v_BlockSE == occupied))
        return false;
      else return true;
      break;
    case Rd_South:
      if(p_Direction == Straight && (this->v_BlockSE == occupied || this->v_BlockNE == occupied))
      	return false;
    	else if (p_Direction == TurnRight && (this->v_BlockSE == occupied))
        return false;
    	else if (p_Direction == TurnLeft && (this->v_BlockSE == occupied || this->v_BlockNE == occupied || this->v_BlockNW == occupied))
        return false;
      else return true;
      break;
  }
}

std::vector<Task> TrafficScheduler::fReleaseVehicle()
{
  std::vector<Task> v_VehicleToRelease = {};
  std::vector<Task> v_VehiclesCanBeReleased = {};
  /*
   * Check each all lists to see if they are is empty. If not, add the task at the back 
   * (which is those that come in first) into the list of vehicle to release if the blocks are reservable
   */
	std::vector<std::vector<Task>> v_ListofListsofTask = {this->v_Rd_North_TasksList, 
                                                        this->v_Rd_East_TasksList,
                                                        this->v_Rd_South_TasksList,
                                                        this->v_Rd_West_TasksList}
  for (int v_indx = 0; v_indx < v_ListofListsofTask.size(); v_indx++)
  {
    if (v_ListofListsofTask[v_indx].size() != 0)
    {
      Task v_Task = v_ListofListsofTask[v_indx].back();
    	if (this->fCheckIfBlocksAreReservable(v_Task.fRtRoad(), v_Task.fRtDirection()))
        v_VehiclesCanBeReleased.push_back(v_Task); 	
  	}
  }
  // Currently, this iteration only release 1 task at a time for a simple implimentation (multiple release can be done later)
  
  // Check which tasks to actually release (only for list that is bigger than 1)
  if (v_VehiclesCanBeReleased.size() > 1)
  {
    // First, assign the first element that can be released to the to release vector
    v_VehicleToRelease.push_back(v_VehiclesCanBeReleased.front());
    // Loop through the rest of the elements
    for (int v_indx = 1; v_indx < v_VehiclesToRelease.size(); v_indx++)
    {
      // If the task that in the to be released comes later than the task that can be released
      if (v_VehicleToRelease[0].fRtArrivalTime() > v_VehiclesCanBeReleased[v_indx].fRtArrivalTime())
        // Swap to the earlier task
        v_VehicleToRelease[0] = v_VehiclesCanBeReleased[v_indx];
    	// If the arrival time is the same...
      else if(v_VehicleToRelease[0].fRtArrivalTime() == v_VehiclesCanBeReleased[v_indx].fRtArrivalTime())
      /* Choose the one that is higher on the prority list 
       * (turn right -> straight -> turn left) 
       * The priority is based on the number of blocks that need to be reserved*/
      {
        // So this meant that the change only happen if the priority of the currently selected is higher (inverted priotity)
        if(v_VehicleToRelease[0].fRtDirection() > v_VehiclesCanBeReleased[v_indx].fRtDirection())
          v_VehicleToRelease[0] = v_VehiclesCanBeReleased[v_indx];
      }
    }
  }
	else
    v_VehicleToRelease = v_VehiclesCanBeReleased;
  
  // Reserve the blocks
  this -> fReserveBlocks(v_VehicleToRelease[0].fRtRoad(), v_VehicleToRelease[0].fRtDirection());
	// Check the road of each vehicle to release to remove the task from the queue
  for (int v_indx = 0; v_indx < v_VehiclesToRelease.size(); v_indx++)
  {
    switch (v_VehiclesToRelease[v_indx].fRtRoad())
    {
      case Rd_North:
        this->v_Rd_North_TasksList.pop_back();
        break;
      case Rd_East:
        this->v_Rd_East_TasksList.pop_back();
        break;
      case Rd_South:
        this->v_Rd_South_TasksList.pop_back();
        break;
      case Rd_West:
        this->v_Rd_West_TasksList.pop_back();
        break;
    }
  }
  
	return v_VehiclesToRelease;
}

void TrafficScheduler::fAddTaskToList(std::vector<Task> p_NewTaskPool)
{
	for (int v_Indx = 0; v_Indx < p_NewTaskPool.size(); v_Indx++)
	{
		Task v_NewTask = p_NewTaskPool[v_Indx];
		// Assign task ID to the task
    v_NewTask.fAssignTaskID(this->v_NextTaskID);
    // Increase the task ID count
    this->v_NextTaskID++;
    // Set the time of task arrival for comparison later to see which task comes first
    v_NewTask.fAssignArrivalTime(std::clock());
    // Switch case to assign the task to their respective vector
		switch (v_NewTask.fRtRoad())
		{
		case Rd_East:
			this->v_Rd_East_TasksList.insert(this->v_Rd_East_TasksList.begin(), v_NewTask);
			break;
		case Rd_West:
			this->v_Rd_West_TasksList.insert(this->v_Rd_West_TasksList.begin(), v_NewTask);
			break;
		case Rd_North:
			this->v_Rd_North_TasksList.insert(this->v_Rd_North_TasksList.begin(), v_NewTask);
			break;
		case Rd_South:
			this->v_Rd_South_TasksList.insert(this->v_Rd_South_TasksList.begin(), v_NewTask);
			break;
		}
	}
}

bool TrafficScheduler::fRtBlockState_SE()
{
  return this->v_BlockSE;
}
bool TrafficScheduler::fRtBlockState_NE()
{
  return this->v_BlockNE;
}
bool TrafficScheduler::fRtBlockState_SW()
{
  return this->v_BlockSW;
}
bool TrafficScheduler::fRtBlockState_NW()
{
  return this->v_BlockNW;
}

