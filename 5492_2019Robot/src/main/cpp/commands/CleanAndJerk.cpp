/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CleanAndJerk.h"
#include "commands/SpotMe.h"
#include "commands/BicepCurl.h"
#include "commands/DeadLift.h"
#include "commands/Flex.h"
CleanAndJerk::CleanAndJerk(double setPoint[2]) {
  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.
    AddSequential(new SpotMe(0));
    AddSequential(new BicepCurl(setPoint[0]));
    AddSequential(new SpotMe(setPoint[1]));
    AddParallel(new Flex());
    AddSequential(new DeadLift());

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
}
