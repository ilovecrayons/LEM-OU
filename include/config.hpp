#pragma once
#include "main.h"
using namespace pros;

// externalize device configurations

extern ADIDigitalOut right_wings;
extern ADIDigitalOut left_wings;
extern ADIDigitalOut back_wings;
extern ADIDigitalOut left_hang_piston;
extern ADIDigitalOut right_hang_piston;

extern Motor intake;
extern Motor shooter;
extern Motor left_front_motor;
extern Motor left_middle_motor;
extern Motor left_back_motor;
extern Motor right_front_motor;
extern Motor right_middle_motor;
extern Motor right_back_motor;

extern MotorGroup left_motors;
extern MotorGroup right_motors;

extern lemlib::Chassis lem;
extern Drive easy;

extern Controller master;

class catapult // creates the catapult class
{
public:
  bool is_continuous{false}; // whether the catapult is set to continuous fire
  bool override{false};      // whether to manually override catapult control
  int state{0};   // the state of the catapult. 0: unloaded. 1: loading. 2:
                  // loaded. 3:continuous
  void lower();   // Declare reset function
  void control(); // declare the control function
};

extern catapult cata; // creates an instance of the catapult object
