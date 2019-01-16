/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <commands/TankDrive.h>
#include "Robot.h"
#include "OI.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
TankDrive::TankDrive() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_drivebase);
}

// Called just before this Command runs the first time
void TankDrive::Initialize() {
  Robot::m_drivebase.DriveBaseInit();
}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {
  if (Robot::m_oi.ReturnDriverXButton())
  {
    double Kp = -0.1;
    double adjust = 0;
    double min_command = .05;
    if (Robot::targetOffsetAngle_Horizontal > 0)
    {
      adjust = Kp*Robot::targetOffsetAngle_Horizontal - min_command;
    }
    else
    {
      adjust = Kp*Robot::targetOffsetAngle_Horizontal + min_command;
    }

    Robot::m_drivebase.ArcadeDrive(adjust, Robot::m_oi.ReturnDriverYAxis());
  }
  else{
    Robot::m_drivebase.ArcadeDrive(Robot::m_oi.ReturnDriverXAxis(), Robot::m_oi.ReturnDriverYAxis());
  }
}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TankDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {}
