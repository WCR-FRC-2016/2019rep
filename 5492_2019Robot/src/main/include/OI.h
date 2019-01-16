  /*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/XboxController.h>
class OI {
 public:
  OI(); 
	double ReturnDriverXAxis();
	double ReturnDriverYAxis();
	void OIInit();
	double DeadBand(double joystick);
	double ReturnManualLeftYAxis();
	bool ReturnDriverXButton();
 private:
  frc::XboxController * _driverStick;
	frc::XboxController * _manualStick;
};
