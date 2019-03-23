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
    LiftLeader->SetSelectedSensorPosition(0,0,50);
    LiftLeader->Config_kP(0, liftP, 0);
    LiftLeader->Config_kI(0, liftI, 0);
    LiftLeader->Config_kD(0, liftD, 0);
}
void DoWeEvenLift::Lift(double joystick){
  if (joystick == 0){
       if (something){
         currentPosition = LiftLeader->GetSelectedSensorPosition(0);
         something = false;
       }
        LiftLeader->Config_kP(0, liftManP, 0);
        LiftLeader->Config_kI(0, liftManI, 0);
        LiftLeader->Config_kD(0, liftManD, 0);
        LiftLeader->Set(ctre::phoenix::motorcontrol::ControlMode::Position,static_cast<double>(currentPosition));
   }
    else{
      something = true;
      LiftLeader->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,joystick/1.333);
    }
}

void DoWeEvenLift::ResetSomething()
{
  something = true;
}


void DoWeEvenLift::ChonkySquat(int setPoint){
    LiftLeader->Config_kP(0, armP, 0);
    LiftLeader->Config_kI(0, armI, 0);
    LiftLeader->Config_kD(0, armD, 0);
    if  (abs (abs(LiftLeader->GetSelectedSensorPosition(0)) - abs(setPoint)) < liftError){
      something = true;
      currentPosition = LiftLeader->GetSelectedSensorPosition(0);
      LiftLeader->Set(ctre::phoenix::motorcontrol::ControlMode::Position, static_cast<double>(currentPosition));
    }
    else{
      something = true;
      currentPosition = LiftLeader->GetSelectedSensorPosition(0);  
      LiftLeader->Set(ctre::phoenix::motorcontrol::ControlMode::Position, static_cast<double>(setPoint));
    }
}
bool DoWeEvenLift::WeighIn(int setPoint){
  bool placeHolder = (setPoint == 0 && LiftLeader->GetSensorCollection().IsFwdLimitSwitchClosed());
  return ((abs(LiftLeader->GetSelectedSensorPosition(0) - setPoint) < liftError) || placeHolder );
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
