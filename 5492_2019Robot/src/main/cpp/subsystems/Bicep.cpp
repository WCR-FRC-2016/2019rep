/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Bicep.h"
#include "RobotMap.h"
#include "OI.h"
#include <frc/Commands/Scheduler.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/RobotDrive.h>
#include <iostream>
#include "Robot.h"
#include <ctre/Phoenix.h>
#include <OpenOneMotor.h>
#include "commands/Flex.h"
#include "RobotMap.h"
WPI_TalonSRX* ArmLeader;
WPI_TalonSRX* ArmFollower;
Bicep::Bicep() : Subsystem("Bicep") {}
void Bicep::BicepStretch(){
  initialized = true;
  OpenOneMotor* OpenBicepMotor =  new OpenOneMotor();
  ArmLeader = OpenBicepMotor->Open(arm1);
  //OpenBicepMotor->Invert = true;
  ArmLeader->SetSelectedSensorPosition(0,0,50);
  ArmFollower = OpenBicepMotor->Open(arm2);
  ArmFollower->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, arm1);
  ArmLeader->Config_kP(0, armP, 0);
  ArmLeader->Config_kI(0, armI, 0);
  ArmLeader->Config_kD(0, armD, 0);
}
void Bicep::Rotato(double joystick) {
    double stayPut = 0;
    double currentPosition = ArmLeader->GetSelectedSensorPosition(0);
    
    if (joystick == 0){
     if (abs(currentPosition) > armCramps)
     {
       stayPut = armStopIt * (abs(currentPosition)/currentPosition);
      }
    }
    else{
      stayPut = 0;
  }
  ArmLeader->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,joystick/3 + stayPut);
  
}
void Bicep::BicepCurl(double setPoint){
  if (abs(abs(ArmLeader->GetSelectedSensorPosition(0)) - setPoint) < armError)
  {
    ArmLeader->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
  }
  else{
     ArmLeader->Set(ctre::phoenix::motorcontrol::ControlMode::Position,setPoint);
  }
 
}
bool Bicep::WeighIn(double setPoint){
  if ((Robot::m_oi.ReturnManualLeftYAxis() != 0) || (Robot::m_oi.ReturnManualRightYAxis() != 0)) {
    frc::Scheduler::GetInstance()->RemoveAll();
  }
  return (abs(ArmLeader->GetSelectedSensorPosition(0) - setPoint) < armError);
}
double Bicep::ReturnBicepEncoder(){
  return ArmLeader->GetSelectedSensorPosition(0);
}
void Bicep::InitDefaultCommand() {
  if (!initialized)
  {
    Robot::m_bicep.BicepStretch();
  }
  Robot::m_bicep.SetDefaultCommand(new Flex());
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
