#include "Task.h"
#include "TrafficScheduler.h"

TaskHandle_t* StartupTask;
TaskHandle_t* ForRoadTask;

//Pinout Map
#define BlockNE_Light 23            //GPIO34
#define BlockSE_Light 18                   
#define BlockSW_Light 19                 
#define BlockNW_Light 21 
unsigned long lastMillis;
// Instanciate a traffic scheduler instance
TrafficScheduler Scheduler;
// A vector for tasks list
std::vector<Task> newTasks;

int VehicleIDCount = 0;



void setup() {
  Serial.begin(115200);
  //Pin Mode
  pinMode(BlockNE_Light, OUTPUT);
  pinMode(BlockSW_Light, OUTPUT);
  pinMode(BlockNW_Light, OUTPUT);
  pinMode(BlockSE_Light, OUTPUT);
  lastMillis = millis();
  
  //pinMode(ReleaseButton_N, INPUT);
  //pinMode(ReleaseButton_W, INPUT);
  //pinMode(ReleaseButton_S, INPUT);
  //pinMode(ReleaseButton_E, INPUT);
  
  Serial.println("Starting Tasks pinning to core.");
  // Startup Task
  xTaskCreate(
    Print,      // Function that should be called
    "Vehicle scheduler",    // Name of the task (for debugging)
    4000,               // Stack size (bytes)
    NULL,               // Parameter to pass
    2,                  // Task priority
    StartupTask               // Task handle
  );
  
  delay(50); 
  
  xTaskCreate(
    Print,           // Function that should be called
    "LED functions",    // Name of the task (for debugging)
    4000,               // Stack size (bytes)
    NULL,               // Parameter to pass
    1,                  // Task priority
    ForRoadTask               // Task handle
  );
  delay(50); 
}


void SchedulerTask(void*)
{
  if (millis() - lastMillis > 3000)
  {
    if (!random(5)) // Random chance for a car to be generated on North Road (1/5 chance)
    {
      Task TaskN(VehicleIDCount, Rd_North, random(3));  // Randomizer to decide the travel direction
      newTasks.push_back(TaskN);
      Serial.print("Vechicle departs from the North, VehicleID: "); //test print
      Serial.println(VehicleIDCount);
      VehicleIDCount++; //Update Vechicle ID
    }
    if(!random(5)) // Random chance for a car to be generated on East Road (1/5 chance)
    {
      Task TaskN(VehicleIDCount, Rd_East, random(3));
      newTasks.push_back(TaskN);
      Serial.print("Vechicle departs from the North, VehicleID: ");//test print
      Serial.println(VehicleIDCount);
      VehicleIDCount++;//Update Vechicle ID
    }
    if(!random(5)) // Random chance for a car to be generated on South Road (1/5 chance)
    {
      Task TaskN(VehicleIDCount, Rd_South, 1);
      newTasks.push_back(TaskN);
      Serial.print("Vechicle departs from the South, VehicleID: ");//test print
      Serial.println(VehicleIDCount);
      VehicleIDCount++;//Update Vechicle ID
    }
    if(!random(5)) // Random chance for a car to be generated on West Road (1/5 chance)
    {
      Task TaskN(VehicleIDCount, Rd_West, random(3));
      newTasks.push_back(TaskN);
      Serial.print("Vechicle departs from the West, VehicleID: ");//test print
      Serial.println(VehicleIDCount);
      VehicleIDCount++;//Update Vechicle ID
    }
    lastMillis = millis();
  }
  
  // Check button for car and create that car as a task then add it to the new task list.
  //check for button press
  
  // Add cars to task list for scheduler 
  Scheduler.fAddTaskToList(newTasks);
  // Release next vehicle
  std::vector<Task> NextVehicle_V = Scheduler.fReleaseVehicle();
  if (NextVehicle_V.size())
  {
    Serial.print("Released a vehicle! Vehicle ID: ");
    Serial.print(NextVehicle_V[0].fRtVehicleID());
    Serial.print(" Road: ");
    Serial.print(NextVehicle_V[0].fRtRoad());
    Serial.print(" Direction: ");
    Serial.println(NextVehicle_V[0].fRtDirection());
    // TODO: Turn on light for released car? Maybe maybe not
  }
    
  
  
  // Reset the next task and list for next run
  newTasks.clear();
}

void RoadTask(void*)
{
  // turn off the leds & unreserve blocks if occupied after a certain amount of time
  // else turn on light if block is occupied
  if (Scheduler.fRtBlockState_NE() == occupied) 
  {
    if (Scheduler.v_Block_NEDirection == Rd_South && millis()-Scheduler.v_Block_NECounter > 6000)
    {
      digitalWrite(BlockNE_Light, LOW);
      Scheduler.fUnreserveBlock(BlockNE);
    }
    else if (Scheduler.v_Block_NEDirection == Rd_East && millis()-Scheduler.v_Block_NECounter > 3000)
    {
      digitalWrite(BlockNE_Light, LOW);
      Scheduler.fUnreserveBlock(BlockNE);
    }
    else if (Scheduler.v_Block_NEDirection == Rd_West && millis()-Scheduler.v_Block_NECounter > 9000)
    {
      digitalWrite(BlockNE_Light, LOW);
      Scheduler.fUnreserveBlock(BlockNE);
    }
    else
      digitalWrite(BlockNE_Light, HIGH);
  }
//=================    
  if (Scheduler.fRtBlockState_SW() == occupied) 
  {
    if (Scheduler.v_Block_SWDirection == Rd_North && millis()-Scheduler.v_Block_SWCounter > 6000)
    {
      digitalWrite(BlockSW_Light, LOW);
      Scheduler.fUnreserveBlock(BlockSW);
    }
    else if (Scheduler.v_Block_SWDirection == Rd_West && millis()-Scheduler.v_Block_SWCounter > 3000)
    {
      digitalWrite(BlockSW_Light, LOW);
      Scheduler.fUnreserveBlock(BlockSW);
    }
    else if (Scheduler.v_Block_SWDirection == Rd_East && millis()-Scheduler.v_Block_SWCounter > 9000)
    {
      digitalWrite(BlockSW_Light, LOW);
      Scheduler.fUnreserveBlock(BlockSW);
    }
    else
      digitalWrite(BlockSW_Light, HIGH);
  }
  
//================  
  if (Scheduler.fRtBlockState_NW() == occupied) 
  {
    if (Scheduler.v_Block_NWDirection == Rd_East && millis()-Scheduler.v_Block_NWCounter > 6000)
    {
      digitalWrite(BlockNW_Light, LOW);
      Scheduler.fUnreserveBlock(BlockNW);
    }
    else if (Scheduler.v_Block_NWDirection == Rd_North && millis()-Scheduler.v_Block_NWCounter > 3000)
    {
      digitalWrite(BlockNW_Light, LOW);
      Scheduler.fUnreserveBlock(BlockNW);
    }
    else if (Scheduler.v_Block_NWDirection == Rd_South && millis()-Scheduler.v_Block_NWCounter > 9000)
    {
      digitalWrite(BlockNW_Light, LOW);
      Scheduler.fUnreserveBlock(BlockNW);
    }
    else
      digitalWrite(BlockNW_Light, HIGH);
  }

//================   
  if (Scheduler.fRtBlockState_SE() == occupied)
  {
    if (Scheduler.v_Block_SEDirection == Rd_West && millis()-Scheduler.v_Block_SECounter > 6000)
    {
      digitalWrite(BlockSE_Light, LOW);
      Scheduler.fUnreserveBlock(BlockSE);
    }
    else if (Scheduler.v_Block_SEDirection == Rd_South && millis()-Scheduler.v_Block_SECounter > 3000)
    {
      digitalWrite(BlockSE_Light, LOW);
      Scheduler.fUnreserveBlock(BlockSE);
    }
    else if (Scheduler.v_Block_SEDirection == Rd_North && millis()-Scheduler.v_Block_SECounter > 9000)
    {
      digitalWrite(BlockSE_Light, LOW);
      Scheduler.fUnreserveBlock(BlockSE);
    }
    else
      digitalWrite(BlockSE_Light, HIGH);
  }
  
}

void Print(void*)
{
  Serial.println("Hi");
}

void loop()
{
}
