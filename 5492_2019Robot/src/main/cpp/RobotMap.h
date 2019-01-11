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
//Collector
const int leftCollector = 10;
const int rightCollector = 11;
//Climb
const int climb1 = 2;
const int climb2 = 3;
//Elevator
const int elevator1 = 4;
const int elevator2 = 5;
//Pneumatics
const int pneuamticValve1 = 7;
const int pneumaticValve2 = 8;

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
