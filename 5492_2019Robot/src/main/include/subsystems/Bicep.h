/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

class Bicep : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  bool initialized = false;
 public:
  Bicep();
  void BicepStretch();
  void Rotato(double joystick);
  void BicepCurl(double setPoint);
  bool WeighIn(double setPoint);
  void InitDefaultCommand() override;
  double ReturnBicepEncoder();
};
