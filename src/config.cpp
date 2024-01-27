#include "config.hpp"
#include "main.h"
#include "pros/adi.hpp"

// ANCHOR device port configuration

constexpr int LEFT_FRONT_PORT{-4};
constexpr int LEFT_MIDDLE_PORT{-2};
constexpr int LEFT_BACK_PORT{-3};
constexpr int RIGHT_FRONT_PORT{17};
constexpr int RIGHT_MIDDLE_PORT{5};
constexpr int RIGHT_BACK_PORT{6};

constexpr int INTAKE_PORT{-14};
constexpr int SHOOTER_PORT{-12};

constexpr int INERTIAL_SENSOR_PORT{11};

#define FRONT_WINGS_PORT 'A'
#define BACK_WINGS_PORT 'B'
#define HANG_PORT 'C'
#define BUMPER_PORT 'D'

// ANCHOR Robot setup

pros::Controller master(CONTROLLER_MASTER);

// Defines motors:

pros::Motor left_front_motor(LEFT_FRONT_PORT,
                             pros::E_MOTOR_GEAR_BLUE); // blue cartridge, 11W
pros::Motor left_middle_motor(LEFT_MIDDLE_PORT,
                              pros::E_MOTOR_GEARSET_06); // blue cartridge, 11W
pros::Motor left_back_motor(LEFT_BACK_PORT,
                            pros::E_MOTOR_GEAR_BLUE); // blue cartridge, 11W
pros::Motor right_front_motor(RIGHT_FRONT_PORT,
                              pros::E_MOTOR_GEAR_BLUE); // blue cartridge, 11W
pros::Motor right_middle_motor(RIGHT_MIDDLE_PORT,
                               pros::E_MOTOR_GEARSET_06); // blue cartridge, 11W
pros::Motor right_back_motor(RIGHT_BACK_PORT,
                             pros::E_MOTOR_GEAR_BLUE); // blue cartridge, 11W

pros::MotorGroup left_motors({left_front_motor, left_middle_motor,
                              left_back_motor});
pros::MotorGroup right_motors({right_front_motor, right_middle_motor,
                               right_back_motor});

pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEAR_BLUE); // blue cartridge, 11W
pros::Motor shooter(SHOOTER_PORT, pros::E_MOTOR_GEAR_RED); // red cartridge, 11W

// Define pneumatics:

pros::ADIDigitalOut front_wings(FRONT_WINGS_PORT);   // wing mechanism piston
pros::ADIDigitalOut back_wings(BACK_WINGS_PORT); // wing mechanism piston
pros::ADIDigitalOut hang_piston(HANG_PORT);        // hang piston

// Define sensors:


pros::Imu inertial_sensor(INERTIAL_SENSOR_PORT); // inertial sensor

// auto selecter bumper switch
pros::ADIDigitalIn bumper(BUMPER_PORT); // bumper sensor

// ANCHOR Chassis class
lemlib::Drivetrain drivetrain{
    &left_motors,  // left drivetrain motors
    &right_motors, // right drivetrain motors
    11.125,         // track width
    3.25,          // wheel diameter
    450,           // wheel rpm
    1.5              // chase power
};

lemlib::OdomSensors sensors{nullptr, nullptr, nullptr, nullptr,
                            &inertial_sensor};

lemlib::ControllerSettings lateralController{
    14,  // kp
    0,   // ki
    21,  // kd
    0,   // windup range
    1,   // small error range
    100, // small timeout
    3,   // big error range
    500, // big error timeout
    15    // slew
};

lemlib::ControllerSettings angularController{
    2,   // kp
    0.2, // ki
    12,  // kd
    10,  // windup range
    1,   // small error range
    50,  // small timeout
    2,   // big error range
    200, // big error timeout
    0    // slew
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController,
                        sensors);


// ANCHOR catapult control
void catapult::lower() { // catapult reset function
  while (shooter.get_power() < 10) {   // executes while catapult is not at the desired angle
    shooter = 127; // outputs power to the catapult motor
    pros::delay(10);
  }
  shooter.brake(); // stops the catapult motor
  state = 2;       // sets the state to "loaded"
}

// ANCHOR async cata implementation
void catapult::control() {
  shooter.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  while (true) {
    if (shooter.get_power() < 4 && cata.state != 1 &&
        cata.state != 3) // checks if the catapult should be lowered
    {
      cata.state = 1;
      cata.lower();
    }
    if (cata.state == 3) // if cata is set to continuous
    {
      shooter = 127;
    }
    pros::delay(15);
  }
}

catapult cata; // creates an instance of the catapult object
