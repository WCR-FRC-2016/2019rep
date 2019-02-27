/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/Servo.h>

class DoWeEvenSee : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  bool DoWeEvenSeeInitialized = false;
  frc::Servo* Sternocleidomastoid;

 public:
  DoWeEvenSee();
  void InvestingFascia();
  void CameraInit();
  void InitDefaultCommand() override;
};