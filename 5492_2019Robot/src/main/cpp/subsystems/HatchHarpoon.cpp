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
#include "commands/SpearedWhale.h"
WPI_TalonSRX* HatchHarpoonMotor;

HatchHarpoon::HatchHarpoon() : Subsystem("ExampleSubsystem") {}
void HatchHarpoon::HatchHarpoonInit() {
  initialized = true;
  OpenOneMotor* OpenHatchHarpoonMotor = new OpenOneMotor();
  HatchHarpoonMotor = OpenHatchHarpoonMotor-> Open(harpoon);
  HatchHarpoonMotor->ConfigForwardLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector,ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled,0);
  HatchHarpoonMotor->ConfigReverseLimitSwitchSource(ctre::phoenix::motorcontrol::LimitSwitchSource::LimitSwitchSource_FeedbackConnector,ctre::phoenix::motorcontrol::LimitSwitchNormal_Disabled,0);
  CurrentState = FreeWilly();
}

int HatchHarpoon::FreeWilly(){
  int ForwardLimit = HatchHarpoonMotor->GetSensorCollection().IsFwdLimitSwitchClosed();
  int BackwardLimit = HatchHarpoonMotor->GetSensorCollection().IsRevLimitSwitchClosed();
  //printf("ForwardLimit=%i",ForwardLimit," BackwardLimit=%i\n", BackwardLimit);
  if (ForwardLimit==1 && BackwardLimit==0){
    return CLOSED;
  }
  else if (ForwardLimit==1 && BackwardLimit==1){
    return MID;
  }
  else if (ForwardLimit==0 && BackwardLimit==1){
    return OPEN;
  }
  else {
    return OPEN;
  }
}

void HatchHarpoon::HarpoonLauncher(){
  //printf("Current state is %i\n",CurrentState);
  switch(CurrentState){
    case OPEN:
    {
      if (Robot::m_oi.ReturnManualLeftBump()){
        CurrentMotor = BackwardMotor;
        CurrentState = GotoMid;
      }
      else if (Robot::m_oi.ReturnManualLeftTrigger()){
        CurrentMotor = BackwardMotor;
        CurrentState = GotoClosed;
      }
      else 
      {
        CurrentMotor = 0;
      }
    }
    break;
    case MID:
      if (Robot::m_oi.ReturnManualLeftBump()){
        CurrentMotor = ForwardMotor;
        CurrentState = GotoOpen;
      }
      else if (Robot::m_oi.ReturnManualLeftTrigger()){
        CurrentMotor = BackwardMotor;
        CurrentState = GotoClosed;
      }
      else 
      {
        CurrentMotor = 0;
      }
    break;
    case CLOSED:
      if (Robot::m_oi.ReturnManualLeftBump()){
        CurrentMotor = ForwardMotor;
        CurrentState = GotoMid;
      }
      else 
      {
        CurrentMotor = 0;
      }
    break;
  
    case GotoOpen:
      if (FreeWilly()==OPEN){
        CurrentState = OPEN;
        CurrentMotor = 0;
      }
    break;
    case GotoMid:
      if (FreeWilly()==MID){
        CurrentState = MID;
        CurrentMotor = 0;
      }
    break;
    case GotoClosed: 
      if (FreeWilly()==CLOSED){
        CurrentState = CLOSED;
        CurrentMotor = 0;
      }
    break;
  }
  HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, CurrentMotor);
}

void HatchHarpoon::InitDefaultCommand() {
  if (!initialized) {
    Robot::m_hatchharpoon.HatchHarpoonInit();
	}
  Robot::m_hatchharpoon.SetDefaultCommand(new SpearedWhale()); 
}

// Put methods for controlling this subsystem
// here. Call these from Commands.