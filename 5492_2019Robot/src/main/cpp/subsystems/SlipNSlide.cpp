/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SlipNSlide.h"
#include "Robot.h"
#include "commands/BananaPeel.h"
#include "OpenOneMotor.h"
#include "RobotMap.h"
WPI_TalonSRX* SlideMotor;
SlipNSlide::SlipNSlide() : Subsystem("SlipNSlide") {}
void SlipNSlide::Inflate(){
  init = true;
  OpenOneMotor* OpenSlideMotor = new OpenOneMotor();
  SlideMotor = OpenSlideMotor-> Open(slide);
}
void SlipNSlide::Wee(double motor){
  SlideMotor->Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput,motor);
}
void SlipNSlide::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
