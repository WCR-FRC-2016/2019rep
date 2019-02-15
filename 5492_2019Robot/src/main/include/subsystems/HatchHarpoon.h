/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

class HatchHarpoon : public frc::Subsystem {
 private:
  int initialized;

 public:
  HatchHarpoon();
  void InitDefaultCommand() override;
  void HatchHarpoonInit();
  int FreeWilly();
  void HarpoonLauncher();
  enum PositionState {
    CLOSED, MID, OPEN, GotoClosed, GotoMid, GotoOpen
  };
  int CurrentState;
  double CurrentPosition = 0;
};
