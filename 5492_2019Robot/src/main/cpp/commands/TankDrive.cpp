/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <commands/TankDrive.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Robot.h"
#include "RobotMap.h"
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
    Robot::m_drivebase.RampSwitch(false);
    double Kp = 0.0095;
    double adjust = 0;
    double min_command = .35;
    double* visionArray = Robot::m_oi.ReturnVisionX();
    double offset = visionArray[0];
    double area = visionArray[1];
    double Kpa = (0.0095-0.03)/(6.5-0.03); //(Far away Kp - Close Kp)/ (Far away area - Up close area)
    bool* lightArray = Robot::m_oi.ReturnLightSensors();
    frc::SmartDashboard::PutBoolean("LightSensor1", lightArray[0]);

    Kp = Kpa * area - Kpa * 0.03 + 0.03; // Kp = Kpa * area - Kpa * Close area + Close Kp
    
    if (area == 0) {
      /*if (lightArray[0]){
        adjust = 0.5;
      }
      else if (lightArray[1]) {
        adjust = -0.5;
      }
      else{
        adjust = 0;
      }*/
      //Add back if we use light sensors
      adjust = 0;
    }
    else{
      if (offset > 0)
      {
        adjust = Kp * offset + min_command;
      }
      else
      {
        adjust = Kp * offset - min_command;
      }
    }
    
    Robot::m_drivebase.ArcadeDrive((Robot::m_oi.ReturnDriverYAxis()<=0)?adjust:-adjust, -Robot::m_oi.ReturnDriverYAxis());
    frc::SmartDashboard::PutNumber("Vision Adjustment", adjust);
  }
  else{
    Robot::m_drivebase.RampSwitch(true);
    Robot::m_drivebase.ArcadeDrive(Robot::m_oi.ReturnDriverXAxis(), -Robot::m_oi.ReturnDriverYAxis());
  }
}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TankDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {}
