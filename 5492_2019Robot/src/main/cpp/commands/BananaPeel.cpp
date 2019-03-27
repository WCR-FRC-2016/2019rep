/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BananaPeel.h"
#include "Robot.h"

BananaPeel::BananaPeel() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_slipnslide);
}

// Called just before this Command runs the first time
void BananaPeel::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BananaPeel::Execute() {
  double motor =0.0;
  if (Robot::m_oi.ReturnDriverAButton() && Robot::m_oi.ReturnDriverRightTrigger())
  {
    motor = -1.0;
  }
  else if (Robot::m_oi.ReturnDriverAButton())
  {
    motor = 1.0;
  }
  else{
    motor = 0.0;
  }
  Robot::m_slipnslide.Wee(motor);
}

// Make this return true when this Command no longer needs to run execute()
bool BananaPeel::IsFinished() { return false; }

// Called once after isFinished returns true
void BananaPeel::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BananaPeel::Interrupted() {}
