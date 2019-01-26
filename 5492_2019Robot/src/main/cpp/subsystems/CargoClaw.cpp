/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoClaw.h"
#include "OpenOneMotor.h"
#include "OI.h"
#include "Robot.h"
#include "RobotMap.h"
#include "ctre/Phoenix.h"

WPI_TalonSRX* CargoClawMotor;
double ClawValue = 0;
double ForwardClaw = 0.5;
double BackwardClaw = -0.5;
int LimitSwitch = 0;
CargoClaw::CargoClaw() : Subsystem("CargoClaw") {}

void CargoClaw::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void CargoClaw::InitCargoClaw(){
  OpenOneMotor* OpenCargoClaw = new OpenOneMotor();
  CargoClawMotor = OpenCargoClaw->Open(cargoClaw);
  CargoClawMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,0,0);

}
void CargoClaw::CollectCargo(bool AButton){
  LimitSwitch = CargoClawMotor->GetSensorCollection().IsFwdLimitSwitchClosed();
  if ( AButton && (LimitSwitch == 1)){
    if (ClawValue == 0){
      ClawValue = ForwardClaw;
    }
    else{
      ClawValue = 0;
    }
  }
  else if(AButton && LimitSwitch){
    if (ClawValue == 0){
      ClawValue == BackwardClaw;
    }
    else{
      ClawValue = 0;
    }     
  }
  CargoClawMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, ClawValue);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
