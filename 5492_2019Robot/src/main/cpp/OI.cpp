/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <frc/WPILib.h>
#include <frc/Joystick.h>
#include <frc/GenericHID.h>
#include <frc/XboxController.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/WPILib.h>
#include "commands/CleanAndJerk.h"
#include "RobotMap.h"
#include "commands/FirmlyGraspIt.h"
#include "commands/CargoClawCommand.h"
	
	 
OI::OI() {
 	 _driverStick = 0;
	_manualStick = 0;

	
	table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  // Process operator interface input here.
}
void OI::OIInit(){
  	if (_driverStick == 0)
	{
		_driverStick = new frc::XboxController(0);
	}
	if (_manualStick == 0)
	{
		_manualStick = new frc::XboxController(1);
	}
	LightSensorZero = new frc::DigitalInput(0);
	LightSensorOne = new frc::DigitalInput(1);
	//manButtonX = new frc::JoystickButton(_manualStick, 3);
	//manButtonY = new frc::JoystickButton(_manualStick, 4);
	//manButtonB = new frc::JoystickButton(_manualStick, 2);
	//manButtonA = new frc::JoystickButton(_manualStick, 1);
	double habLevel[2] = {armHab, liftHab};
	double lowLevel[2] = {armLow, liftLow};
	double midLevel[2] = {armMid, liftMid};
	//manButtonX->ToggleWhenPressed(new CleanAndJerk(habLevel));
	//manButtonY->ToggleWhenPressed(new CleanAndJerk(midLevel));
	//manButtonB->ToggleWhenPressed(new CleanAndJerk(lowLevel));
	//manSelect->WhileHeld(new FirmlyGrasp(-manHarpoon));
	//manStart->WhileHeld(new FirmlyGrasp(manHarpoon));
	

}	
bool OI::ReturnDriverBButton() {
	return _driverStick->GetBButtonPressed();
}
bool OI::ReturnDriverYButton(){
	return _driverStick->GetYButtonPressed();
}
double OI::ReturnDriverXAxis(){
	return DeadBand(_driverStick->GetX(frc::GenericHID::kRightHand));

}
bool OI::ReturnManualRightBumper(){
	return _manualStick->GetBumper(frc::GenericHID::kRightHand);
}
double OI::ReturnDriverYAxis(){
	return DeadBand(_driverStick->GetY(frc::GenericHID::kLeftHand));
}

double OI::DeadBand(double joystick) {
	if (-0.1295 < joystick && joystick < 0.1295) {
		joystick = 0;
	}
		return joystick;
}

double OI::ReturnManualLeftYAxis(){
	return DeadBand(_manualStick->GetY(frc::GenericHID::kLeftHand));
}

bool OI::ReturnManualLeftTrigger(){
	return (DeadBand(_manualStick->GetTriggerAxis(frc::GenericHID::kLeftHand)) > 0.5);
}

bool OI::ReturnManualLeftBump(){
	return _manualStick->GetBumper(frc::GenericHID::kLeftHand);
}

bool OI::ReturnDriverXButton() {
	return _driverStick->GetXButton();
}
double OI::ReturnManualRightYAxis(){
	return DeadBand(_manualStick->GetY(frc::GenericHID::kRightHand));
}


void OI::SwapLedMode(int mode)	{
	//1 is off, 3 is on
	table->PutNumber("ledMode",mode);
}

double* OI::ReturnVisionX(){
	targetOffsetAngle_Horizontal = table->GetNumber("tx",0.0); 
	targetArea = table->GetNumber("ta",0.0);
	visionData[0] = targetOffsetAngle_Horizontal;
	visionData[1] = targetArea;
	return visionData;
}
bool* OI::ReturnLightSensors() {
	lightData[0] = LightSensorZero->Get();
	lightData[1] = LightSensorOne->Get();
	return lightData;
}

bool OI::ReturnManualAButton() {
	return _manualStick->GetAButtonPressed();
}
bool OI::ReturnManualXButton(){
	return _manualStick->GetXButton();
}
bool OI::ReturnManualYButton() {
	return _manualStick->GetYButton();	
}
bool OI::ReturnManualBButton() {
	return _manualStick->GetBButton();	
}


