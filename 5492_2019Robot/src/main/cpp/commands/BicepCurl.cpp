/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BicepCurl.h"
#include "Robot.h"
#include "RobotMap.h"

BicepCurl::BicepCurl(double position) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_bicep);
  BicepCurl::SetInterruptible(true);
  setPoint = position;
  setPoint = setPoint * abs(Robot::m_bicep.ReturnBicepEncoder())/Robot::m_bicep.ReturnBicepEncoder();
  
}

// Called just before this Command runs the first time
void BicepCurl::Initialize() {
   
}

// Called repeatedly when this Command is scheduled to run
void BicepCurl::Execute() {
  
  Robot::m_bicep.BicepCurl(setPoint);

}

// Make this return true when this Command no longer needs to run execute()
bool BicepCurl::IsFinished() { 
  return (Robot::m_bicep.WeighIn(setPoint)); 
  }
//returns true after setting setpoint once

// Called once after isFinished returns true
void BicepCurl::End() {

  Robot::m_bicep.Rotato(0);
}
 
// Called when another command which requires one or more of the same
// subsystems is scheduledto run
void BicepCurl::Interrupted()
  
 {
 
 
}
