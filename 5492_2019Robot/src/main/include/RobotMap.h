/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
//Alvin - Basically set ports and talon numbers for talons and controllers.
//Put them here so its all in one place
#pragma once
//Drive Base
const int frontLeftDrive = 14; //encoder
const int frontRightDrive = 1; //encoder
const int backLeftDrive = 15;
const int backRightDrive = 0;

const int RampTime = .5;
//Collector
const int cargoClaw = 5;

//Elevator
const int lift1 = 3;//should be 2 , r2 is swapped
const int lift2 = 2;

const double liftP = 0;
const double liftI = 0;
const double liftD = 0;

const double liftHab = 0;
const double liftLow = 0;
const double liftMid = 0;
const double liftError = 0;
//Pneumatics
const int harpoon = 4;

const double harpoonOpen = 0;
const double harpoonMid = 0;
const double harpoonClosed = 0;
const double manHarpoon = .5; 

const double harpoonP = 0;
const double harpoonI = 0;
const double harpoonD = 0;

//Arm
const int arm1 = 12;
const int arm2 = 13;

const double armP = 0;
const double armI = 0;
const double armD = 0;

const double armHab = 0;
const double armLow = 0;
const double armMid = 0;
const double armError = 0;


const double RightP = 0.0678;
const double RightI = 6.78E-6;
const double RightD = 0;
const double LeftP = 0.073814156 ;
const double LeftI = 7.3814156E-6;
const double LeftD = 0;

const double MaxOutput = 1;
const double NominalOutput = .25;
const double PIDDeadband = 0.011415692;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;
