/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SpearedWhale.h"
#include "subsystems/HatchHarpoon.h"
#include "Robot.h"
SpearedWhale::SpearedWhale() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_hatchharpoon);
}

// Called just before this Command runs the first time
void SpearedWhale::Initialize() {
  Robot::m_hatchharpoon.HatchHarpoonInit();
}
// Called repeatedly when this Command is scheduled to run
void SpearedWhale::Execute() {
  Robot::m_hatchharpoon.HarpoonLauncher();
}

// Make this return true when this Command no longer needs to run execute()
bool SpearedWhale::IsFinished() { return false; }

// Called once after isFinished returns true
void SpearedWhale::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpearedWhale::Interrupted() {}
