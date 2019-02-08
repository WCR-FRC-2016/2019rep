/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DoWeEvenLift.h"
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
#include <commands/DeadLift.h>
WPI_TalonSRX* LiftLeader;
WPI_TalonSRX* LiftFollower;

DoWeEvenLift::DoWeEvenLift() : Subsystem("DoWeEvenLift") {}
void DoWeEvenLift::LiftInit() {
    liftInitialized = true;
    OpenOneMotor* OpenLiftMotor =  new OpenOneMotor();
    LiftLeader = OpenLiftMotor->Open(lift1);
    OpenLiftMotor->Invert = true;
    LiftFollower = OpenLiftMotor->Open(lift2);
    LiftFollower->Set(ctre::phoenix::motorcontrol::ControlMode::Follower, lift1);
}
void DoWeEvenLift::Lift(double joystick){
  if (joystick > 0){
    joystick = joystick / 1;
  }
  else {
    joystick = joystick / 1.5;
  }
  LiftLeader->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, joystick);
}
void DoWeEvenLift::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
    if (!liftInitialized){
      DoWeEvenLift::LiftInit();
    }
    Robot::m_doweevenlift.SetDefaultCommand(new DeadLift() );


}

// Put methods for controlling this subsystem
// here. Call these from Commands.
