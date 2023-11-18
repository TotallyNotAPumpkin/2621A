/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Emily Wang                                                */
/*    Created:      07/30/2023                                                */
/*    Description:  2621 Team Code                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Motor2               motor         9               
// Motor3               motor         2               
// Motor4               motor         10 
// Puncher              motor         8
// Wall                 motor         5
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
competition Competition;

//  ______________
// |              |
// |2            1|   ^
// |              |  /|\
// |              |   |
// |4            3|   |
// | ____________ |
//

// GLOBAL VARIABLES:

// modes:
int driveMode = 0; // 0 = forward, 1 = backward

// buttons:
bool pToggle = false;
// letter buttons:
int stateY = 0;
// arrow buttons:

// trigger buttons:

// MATH STUFF:
double abso(double k) {
    if (k < 0)
        return -k;
    else
        return k;
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
    // NOTE FOR JULIA - function parameters most likely will have to be edited
        // in the future, we'll have the gyro/accelerometer on it so we won't have to do parameter editing and just PID it
        // also in the future I may make these into functions to make it more readable, especially if we have more in auton
        // actually now that I think about it, these will def be turned into functions...

    // move forward
    LeftMotorGroup.spinTo(2, rev, false);
    RightMotorGroup.spinTo(2, rev, true);
    wait(250, msec);

    // resets motors
    LeftMotorGroup.resetPosition();
    RightMotorGroup.resetPosition();

    // turn right
    LeftMotorGroup.spinTo(2, rev, false);
    RightMotorGroup.spinTo(-2, rev, true);
    wait(250, msec);

    // puncher boom boom boom
    pMotor.spin(forward, 37, percent);

    // wall thing that I have not coded for auton
}


/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
    while (true) {
        // right stick, up - down
        double rightPos = Controller1.Axis2.position(percent);
        // left stick, up - down
        double leftPos = Controller1.Axis3.position(percent);

        // puncher code (boom boom boom like a gun!) - NOTE FOR JULIA - THE PERCENT SPEED MAY HAVE TO BE EDITED DURING TESTING
        if(Controller1.ButtonR1.pressing()) {
            pMotor.spin(forward, 35, percent);
        } else {
            pMotor.stop();
        }

        // puncher toggle button (aka superspeed no assisstance boom boom boom *note, not actually superspeed)
        if(Controller1.ButtonL1.pressing()) {
            if(pToggle) {
                pMotor.spin(forward, 35, percent);
                pToggle = false;
            } else {
                pMotor.stop();
                pToggle = true;
            }
            // prevents overload or smth prob
            vex::task::sleep(150);
        }


        // allows for co-driver to contribute (please don't use this, only have one driver present atm as I'm not sure if punchy and wall will mess it up)
        if (Controller2.installed()) {
            double rightPos2 = Controller2.Axis2.position();
            double leftPos2 = Controller2.Axis3.position();

            if (abso(rightPos2) > abso(rightPos))
                rightPos = rightPos2;
            if (abso(leftPos2) > abso(leftPos))
                leftPos = leftPos2;
        }

        // forward = forward of robot
        if(driveMode == 0) {
          LeftMotorGroup.spin(directionType::fwd, leftPos, velocityUnits::pct);
          RightMotorGroup.spin(directionType::fwd, rightPos, velocityUnits::pct);
        }

        // forward = backward of robot
        if(driveMode == 1) {
          LeftMotorGroup.spin(directionType::fwd, -leftPos, velocityUnits::pct);
          RightMotorGroup.spin(directionType::fwd, -rightPos, velocityUnits::pct);
        }
        vex::task::sleep(20); // Sleep to prevent hogging the CPU
    }
}


// runs all the functions above!
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}