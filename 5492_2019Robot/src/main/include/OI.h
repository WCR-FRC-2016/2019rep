/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/XboxController.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/WPILib.h>
class OI {
 public:
  OI(); 
	double ReturnDriverXAxis();
	double ReturnDriverYAxis();
	void OIInit();
	double DeadBand(double joystick);
	double ReturnManualLeftYAxis();
	bool ReturnDriverXButton();
	double visionData[2] = {0.0,0.0};
	bool* ReturnLightSensors();
	bool lightData[2] = {false,false}; 
	
	double targetOffsetAngle_Horizontal;
  double targetOffsetAngle_Vertical;
  double targetArea;
  double targetSkew;
	nt::NetworkTableEntry ledmode;
	std::shared_ptr<NetworkTable> table;
	double* ReturnVisionX();
	
 private:
  frc::XboxController * _driverStick;
	frc::XboxController * _manualStick;
	frc::DigitalInput* LightSensorZero;
	frc::DigitalInput* LightSensorOne;
};
