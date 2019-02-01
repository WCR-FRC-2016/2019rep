/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeadLift.h"
#include "subsystems/DoWeEvenLift.h"
#include "OI.h"
#include "RobotMap.h"
#include "Robot.h"
DeadLift::DeadLift() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_doweevenlift);
}

// Called just before this Command runs the first time
void DeadLift::Initialize() {
  Robot::m_doweevenlift.LiftInit();
}

// Called repeatedly when this Command is scheduled to run
void DeadLift::Execute() {
    if(Robot::m_oi.ReturnManualXButton() || State==POS1) {
    Robot::m_doweevenlift.CtrlLift(LiftP1);
    State = POS1;
  }
    if(Robot::m_oi.ReturnManualYButton() || State==POS2) {
    Robot::m_doweevenlift.CtrlLift(LiftP2);
    State = POS2;
  }
    if(Robot::m_oi.ReturnManualBButton() || State==POS3) {
    Robot::m_doweevenlift.CtrlLift(LiftP3);
    State = POS3;
  }
    if(Robot::m_oi.ReturnManualAButton() || State==POS4) {
    Robot::m_doweevenlift.CtrlLift(LiftP4);
    State = POS4;
  }
    if((Robot::m_oi.ReturnManualLeftYAxis() != 0) || State==Man) {
    Robot::m_doweevenlift.Lift(Robot::m_oi.ReturnManualLeftYAxis());
    State = Man;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool DeadLift::IsFinished() { return false; }

// Called once after isFinished returns true
void DeadLift::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeadLift::Interrupted() {}
