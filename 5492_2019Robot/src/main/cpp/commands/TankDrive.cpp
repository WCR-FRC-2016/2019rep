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
  Robot::m_drivebase.reverseDrive(Robot::m_oi.ReturnDriverBButton());
  Robot::m_drivebase.slowDrive(Robot::m_oi.ReturnDriverYButton());
  if (Robot::m_oi.ReturnDriverXButton())
  {
    Robot::m_oi.SwapLedMode(3);
    Robot::m_drivebase.RampSwitch(false);
    double Kp = 0.0095;
    double adjust = 0;
    double min_command = .35;
    double* visionArray = Robot::m_oi.ReturnVisionX();
    double offset = visionArray[0];
    double area = visionArray[1];
    double farKP = 0.0095;
    double closeKP = 0.03;
    double farArea = 6.5;
    double closeArea = 0.03;
    double Kpa = (farKP-closeKP)/(farArea-closeArea); //(Far away Kp - Close Kp)/ (Far away area - Up close area)
    bool* lightArray = Robot::m_oi.ReturnLightSensors();
    frc::SmartDashboard::PutBoolean("LightSensor1", lightArray[0]);

    /*
        Kp    
        |
        |
        |\
        | \
Close KP|--\
        |  |\
        |  | \
        |  |  \
        |  |   \
        |  |    \
        |  |     \
Far KP  |--|----- \
        |  |      |\
        |  |      | \
        |  |      |  \ 
        ------------------------------- Area
          Close  Far
          Area   Area
    */

    Kp = Kpa * area - Kpa * closeArea + closeKP; // Kp = Kpa * area - Kpa * Close area + Close Kp
    double forwardBack = -Robot::m_oi.ReturnDriverYAxis();
    if (area == 0) {
      if ((lightArray[0] && lightArray[1])){ // 0 is left 1 is right, true = Don't see line, false = I see something
        if (!Isee){  // No line seen
          forwardBack = 0.0;
          if (prevError > 0){ // turn right
           adjust = 0.5;
          }
          else{
            adjust = -0.5;
          }
        }
        else{
          adjust = 0;
        }
      }
      else{
        Isee = true;
        if (!lightArray[0]) { // I do see something on the left
        adjust = -0.5;
        }
        else{
        adjust = 0.5;
        }
      }
      
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
    Robot::m_drivebase.ArcadeDrive((Robot::m_oi.ReturnDriverYAxis()<=0)?adjust:-adjust, forwardBack);
    frc::SmartDashboard::PutNumber("Vision Adjustment", adjust);
    prevError = offset;
  }
  else{
    Robot::m_drivebase.RampSwitch(true);
    Robot::m_oi.SwapLedMode(1);
    Robot::m_drivebase.ArcadeDrive(Robot::m_oi.ReturnDriverXAxis(), -Robot::m_oi.ReturnDriverYAxis());
    Isee = false;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() { return false; }

// Called once after isFinished returns true
void TankDrive::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TankDrive::Interrupted() {}
