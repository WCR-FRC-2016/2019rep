/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Flex.h"
#include "Robot.h"
#include "OI.h"
#include "RobotMap.h"

Flex::Flex() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_bicep);
}

// Called just before this Command runs the first time
void Flex::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Flex::Execute() {
  
  if(Robot::m_oi.ReturnManualXButton() || State==POS1) {
    Robot::m_bicep.CtrlRotato(ArmP1);
    State = POS1;
  }
    if(Robot::m_oi.ReturnManualYButton() || State==POS2) {
    Robot::m_bicep.CtrlRotato(ArmP2);
    State = POS2;
  }
    if(Robot::m_oi.ReturnManualBButton() || State==POS3) {
    Robot::m_bicep.CtrlRotato(ArmP3);
    State = POS3;
  }
    if(Robot::m_oi.ReturnManualAButton() || State==POS4) {
    Robot::m_bicep.CtrlRotato(ArmP4);
    State = POS4;
  }
    if((Robot::m_oi.ReturnManualRightYAxis() != 0) || State==Man) {
    Robot::m_bicep.Rotato(Robot::m_oi.ReturnManualRightYAxis());
    State = Man;
  }
}

// Make this return true when this Command no longer needs to run execute()
bool Flex::IsFinished() { return false; }

// Called once after isFinished returns true
void Flex::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Flex::Interrupted() {}
