/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Pectoral.h"
#include "OpenOneMotor.h"
#include "RobotMap.h"
#include <ctre/Phoenix.h>
#include "Robot.h"
#include "commands/PushUp.h"
 WPI_TalonSRX* PectoralMotor;
Pectoral::Pectoral() : Subsystem("Pectoral") {
  
}
void Pectoral::Init(){
  initialized = true;

  OpenOneMotor* OpenPectoralMotor = new OpenOneMotor();
  PectoralMotor = OpenPectoralMotor-> Open(endLift);
}
void Pectoral::UpDown(double motor){
  PectoralMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, motor);
}

void Pectoral::InitDefaultCommand() {
  if (!initialized){
    Robot::m_pectoral.Init();
    
  }
  Robot::m_pectoral.SetDefaultCommand(new PushUp());
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
