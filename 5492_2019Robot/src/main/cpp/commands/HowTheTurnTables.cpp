/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/HowTheTurnTables.h"
#include "Robot.h"

HowTheTurnTables::HowTheTurnTables() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_doweevensee);
}

// Called just before this Command runs the first time
void HowTheTurnTables::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void HowTheTurnTables::Execute() {
  Robot::m_doweevensee.InvestingFascia();
}

// Make this return true when this Command no longer needs to run execute()
bool HowTheTurnTables::IsFinished() { return false; }

// Called once after isFinished returns true
void HowTheTurnTables::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HowTheTurnTables::Interrupted() {}
