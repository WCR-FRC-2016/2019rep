/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchHarpoon.h"
#include "RobotMap.h"
#include "OI.h"
#include <subsystems/DriveBase.h>
#include <frc/Commands/Scheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>
#include "OI.h"
#include <frc/Joystick.h>
#include <frc/RobotDrive.h>
#include <iostream>
#include "Robot.h"
#include <ctre/Phoenix.h>
#include "OpenOneMotor.h"
WPI_TalonSRX* HatchHarpoonMotor;

HatchHarpoon::HatchHarpoon() : Subsystem("ExampleSubsystem") {}

void HatchHarpoon::HatchHarpoonInit() {
  initialized = true;
  OpenOneMotor* OpenHatchHarpoonMotor = new OpenOneMotor();
  HatchHarpoonMotor = OpenHatchHarpoonMotor-> Open(harpoon);
}

int HatchHarpoon::FreeWilly(){
  bool ForwardLimit = HatchHarpoonMotor->GetSensorCollection().IsFwdLimitSwitchClosed();
  bool BackwardLimit = HatchHarpoonMotor->GetSensorCollection().IsRevLimitSwitchClosed();
  if (ForwardLimit && ! BackwardLimit){
    return CLOSED;
  }else if (ForwardLimit && BackwardLimit){
    return MID;
  }else if (!ForwardLimit && BackwardLimit){
    return OPEN;
  }
}

void HatchHarpoon::HarpoonLauncher(){
  switch(FreeWilly()){
    case OPEN:
    {
      if (ReturnManualLeftBump){
        return MID;
      }
      if (ReturnManualLeftTrigger){
        return CLOSED;
      }
    }
    break;
    case MID:
    {
      if (ReturnManualLeftBump){
        return OPEN;
      }
      if (ReturnManualLeftTrigger){
        return CLOSED;
      }
    }
    break;
    case CLOSED:
    {
      if (ReturnManualLeftBump){
        return MID;
      }
    }
    break;
  }
}

void HatchHarpoon::InitDefaultCommand() {
  if (!initialized) {
		HatchHarpoon::HatchHarpoonInit();
	}
	
  //Robot::m_drivebase.SetDefaultCommand(new TankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.