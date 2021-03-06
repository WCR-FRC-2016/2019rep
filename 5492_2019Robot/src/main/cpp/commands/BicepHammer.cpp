/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BicepHammer.h"
#include "Robot.h"
BicepHammer::BicepHammer(int position) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_bicep);
  BicepHammer::SetInterruptible(true);
  setPoint = position;
  firstTime = true;
}

// Called just before this Command runs the first time
void BicepHammer::Initialize() {
  firstTime = true;
}

// Called repeatedly when this Command is scheduled to run
void BicepHammer::Execute() {
    if(firstTime)
    {
    setPoint = abs(setPoint) * (abs(Robot::m_bicep.ReturnBicepEncoder())/Robot::m_bicep.ReturnBicepEncoder());
    firstTime = false;

    }
  
  Robot::m_bicep.BicepCurl(setPoint);

}

// Make this return true when this Command no longer needs to run execute()
bool BicepHammer::IsFinished() { 
  return (Robot::m_bicep.WeighIn(setPoint));  
  }

// Called once after isFinished returns true
void BicepHammer::End() {
  firstTime = true;
  Robot::m_bicep.Rotato(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BicepHammer::Interrupted() {
  firstTime = true;
}
