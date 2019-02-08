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
WPI_TalonSRX* ArmLeader;
WPI_TalonSRX* ArmFollower;
Bicep::Bicep() : Subsystem("Bicep") {}
void Bicep::BicepStretch(){
  initialized = true;
  OpenOneMotor* OpenBicepMotor =  new OpenOneMotor();
  ArmLeader = OpenBicepMotor->Open(arm1);
  OpenBicepMotor->Invert = true;
  ArmFollower = OpenBicepMotor->Open(arm2);
  ArmFollower->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, arm1);
}
void Bicep::Rotato(double joystick) {
  ArmLeader->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,joystick);
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