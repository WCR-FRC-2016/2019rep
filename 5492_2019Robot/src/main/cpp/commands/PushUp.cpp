/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PushUp.h"
#include "OI.h"
#include "Robot.h"
PushUp::PushUp() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_pectoral);
}

// Called just before this Command runs the first time
void PushUp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PushUp::Execute() {
  double motor = 0.0;
  if (Robot::m_oi.ReturnDriverLeftBumper()){
    motor = .60;
  }
  else if (Robot::m_oi.ReturnDriverRightBumper()){
    motor = -0.5;
  }
  else {
    motor = 0.0;
  }
  Robot::m_pectoral.UpDown(motor);
  
}

// Make this return true when this Command no longer needs to run execute()
bool PushUp::IsFinished() { return false; }

// Called once after isFinished returns true
void PushUp::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushUp::Interrupted() {}
