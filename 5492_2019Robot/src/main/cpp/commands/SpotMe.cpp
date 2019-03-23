/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SpotMe.h"
#include "Robot.h"
#include "frc/commands/Scheduler.h"
#include "RobotMap.h"

SpotMe::SpotMe(int position) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_doweevenlift);
  SpotMe::SetInterruptible(true);
  setPoint = position;
}

// Called just before this Command runs the first time
void SpotMe::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SpotMe::Execute() {
  Robot::m_doweevenlift.ChonkySquat(setPoint);
}

// Make this return true when this Command no longer needs to run execute()
bool SpotMe::IsFinished() { return (Robot::m_doweevenlift.WeighIn(setPoint));  }

// Called once after isFinished returns true
void SpotMe::End() {
  Robot::m_doweevenlift.Lift(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpotMe::Interrupted() {
  
  
}
