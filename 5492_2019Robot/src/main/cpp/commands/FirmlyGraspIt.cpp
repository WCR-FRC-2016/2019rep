/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FirmlyGraspIt.h"
#include "Robot.h"
#include "RobotMap.h"

FirmlyGraspIt::FirmlyGraspIt() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_hatchharpoon);

}

// Called just before this Command runs the first time
void FirmlyGraspIt::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FirmlyGraspIt::Execute() {
  double vroom = 0;
  if (Robot::m_oi.ReturnManualLeftBump()){
    vroom = 1;
  }
  else if (Robot::m_oi.ReturnManualLeftTrigger()){
    vroom = -1;
  }
  else{
    vroom = 0;
  }
  Robot::m_hatchharpoon.FirmlyGrasp(vroom);
}

// Make this return true when this Command no longer needs to run execute()
bool FirmlyGraspIt::IsFinished() { return false; }

// Called once after isFinished returns true
void FirmlyGraspIt::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FirmlyGraspIt::Interrupted() {}
