/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Flex.h"
#include "Robot.h"
#include "OI.h"

Flex::Flex() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_bicep);
  Flex::SetInterruptible(true);
}

// Called just before this Command runs the first time
void Flex::Initialize() {
  
}

// Called repeatedly when this Command is scheduled to run
void Flex::Execute() {
  Robot::m_bicep.Rotato(Robot::m_oi.ReturnManualRightYAxis()); // remove '-' for knoxville on R1
}

// Make this return true when this Command no longer needs to run execute()
bool Flex::IsFinished() { return false; }

// Called once after isFinished returns true
void Flex::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Flex::Interrupted() {}
