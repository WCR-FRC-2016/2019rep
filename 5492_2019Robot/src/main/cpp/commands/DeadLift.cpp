/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeadLift.h"
#include "subsystems/DoWeEvenLift.h"
#include "OI.h"
#include "Robot.h"
#include "RobotMap.h"
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
  if (Robot::m_oi.ReturnManualXButton()){
    if (Robot::m_bicep.ReturnBicepEncoder() < 0){
      Robot::m_doweevenlift.ChonkySquat(liftCollect);  
    }
    else{
      Robot::m_doweevenlift.ChonkySquat(liftHab);
    }
  }
  else if (Robot::m_oi.ReturnManualYButton()){
      Robot::m_doweevenlift.ChonkySquat(liftMid);
      Robot::m_bicep.BicepCurl(armMid * abs(Robot::m_bicep.ReturnBicepEncoder())/Robot::m_bicep.ReturnBicepEncoder());
  }
  else
  {
    Robot::m_doweevenlift.Lift(Robot::m_oi.ReturnManualLeftYAxis());
  }
}


// Make this return true when this Command no longer needs to run execute()
bool DeadLift::IsFinished() { return false; }

// Called once after isFinished returns true
void DeadLift::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeadLift::Interrupted() {}
