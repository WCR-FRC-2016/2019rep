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
  
  
  HatchHarpoonMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
  HatchHarpoonMotor->SetSelectedSensorPosition(harpoonMid, 0, 50); // Zero
  HatchHarpoonMotor->SetStatusFramePeriod(StatusFrame::Status_1_General_, 5, 0); //Talon sends new status frame every 5 ms
  HatchHarpoonMotor->SetSensorPhase(false);

  // PID
  HatchHarpoonMotor->Config_kP(0, harpoonP, 0);
  HatchHarpoonMotor->Config_kI(0, harpoonI, 0);
  HatchHarpoonMotor->Config_kD(0, harpoonD, 0);
  CurrentState = GotoOpen;
  CurrentPosition = harpoonOpen;
}

int HatchHarpoon::FreeWilly(){
  int startPosition = HatchHarpoonMotor->GetSelectedSensorPosition(0);
  //printf("ForwardLimit=%i",ForwardLimit," BackwardLimit=%i\n", BackwardLimit);
  if ((startPosition == harpoonClosed) || (HatchHarpoonMotor->GetSensorCollection().IsRevLimitSwitchClosed() == 1)) {
    HatchHarpoonMotor->SetSelectedSensorPosition(0, 0, 50);
    return CLOSED;
  }
  else if (startPosition == harpoonMid){
    return MID;
  }
  else if ((startPosition == harpoonOpen) || (HatchHarpoonMotor->GetSensorCollection().IsFwdLimitSwitchClosed() == 1)){
    HatchHarpoonMotor->SetSelectedSensorPosition(harpoonOpen, 0, 50);
    return OPEN;
  }
  else {
    return CurrentState;
  }
}

void HatchHarpoon::HarpoonLauncher(){
  //printf("Current state is %i\n",CurrentState);
  switch(CurrentState){
    case OPEN:
      if (Robot::m_oi.ReturnManualLeftBump()){
        CurrentPosition = harpoonMid;
        CurrentState = GotoMid;
      }
      else if (Robot::m_oi.ReturnManualLeftTrigger()){
        CurrentPosition = harpoonClosed;
        CurrentState = GotoClosed;
      }
      else 
      {
        CurrentPosition = CurrentPosition;
      }
    
     HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    break;
    case MID:
      if (Robot::m_oi.ReturnManualLeftBump()){
        CurrentPosition = harpoonOpen;
        CurrentState = GotoOpen;
      }
      else if (Robot::m_oi.ReturnManualLeftTrigger()){
        CurrentPosition = harpoonClosed;
        CurrentState = GotoClosed;
      }
      else 
      {
        CurrentPosition = CurrentPosition;
      }
       HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    break;
    case CLOSED:
      if (Robot::m_oi.ReturnManualLeftBump()){
        CurrentPosition = harpoonMid;
        CurrentState = GotoMid;
      }
      else 
      {
        CurrentPosition = CurrentPosition;
      }
      HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    break;
  
    case GotoOpen:
      if (FreeWilly()==OPEN){
        CurrentState = OPEN;
        CurrentPosition = CurrentPosition;
        HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
      }
      else {
        HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::Position, CurrentPosition);
      }
    break;
    case GotoMid:
      if (FreeWilly()==MID){
        CurrentState = MID;
        CurrentPosition = CurrentPosition;
        HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
      }
      else {
        HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::Position, CurrentPosition);
      }
    break;
    case GotoClosed: 
      if (FreeWilly()==CLOSED){
        CurrentState = CLOSED;
        CurrentPosition = CurrentPosition;
        HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
      }
      else {
        HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::Position, CurrentPosition);
      }
    break;
  }
}
void HatchHarpoon::FirmlyGrasp(double motor){
   HatchHarpoonMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, motor);
}
void HatchHarpoon::InitDefaultCommand() {
  if (!initialized) {
    Robot::m_hatchharpoon.HatchHarpoonInit();
	}
  Robot::m_hatchharpoon.SetDefaultCommand(new SpearedWhale()); 
}

// Put methods for controlling this subsystem
// here. Call these from Commands.