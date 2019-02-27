/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DoWeEvenSee.h"
#include "Robot.h"
#include "subsystems/Bicep.h"
#include "RobotMap.h"
#include "commands/HowTheTurnTables.h"
#include <frc/Servo.h>

DoWeEvenSee::DoWeEvenSee() : Subsystem("ExampleSubsystem") {}

void DoWeEvenSee::CameraInit() 
{
  DoWeEvenSeeInitialized = true;
  Sternocleidomastoid = new frc::Servo(1);
            // big neck
}

void DoWeEvenSee::InvestingFascia()
{
  double ArmPosition = Robot::m_bicep.MuscleCam();
  if (ArmPosition < armCenter)
  {
    Sternocleidomastoid->Set(backwardCam);
  }
  else 
  {
    Sternocleidomastoid->Set(forwardCam);
  }
}

void DoWeEvenSee::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
if (!DoWeEvenSeeInitialized) 
{
  DoWeEvenSee::CameraInit();
} 
  Robot::m_doweevensee.SetDefaultCommand(new HowTheTurnTables() );
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
