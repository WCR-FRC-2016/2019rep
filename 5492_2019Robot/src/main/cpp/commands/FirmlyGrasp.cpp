/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/FirmlyGrasp.h"
#include "Robot.h"

FirmlyGrasp::FirmlyGrasp(double motor) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_hatchharpoon);
  vroom = motor;
}

// Called just before this Command runs the first time
void FirmlyGrasp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void FirmlyGrasp::Execute() {
  Robot::m_hatchharpoon.FirmlyGrasp(vroom);
}

// Make this return true when this Command no longer needs to run execute()
bool FirmlyGrasp::IsFinished() { return true; }

// Called once after isFinished returns true
void FirmlyGrasp::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FirmlyGrasp::Interrupted() {}
