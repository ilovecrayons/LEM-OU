#include "config.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"

// ANCHOR device port configuration

constexpr int LEFT_FRONT_PORT{-13};
constexpr int LEFT_MIDDLE_PORT{-12};
constexpr int LEFT_BACK_PORT{-11};
constexpr int RIGHT_FRONT_PORT{18};
constexpr int RIGHT_MIDDLE_PORT{19};
constexpr int RIGHT_BACK_PORT{20};

constexpr int INTAKE_PORT{-21};
constexpr int SHOOTER_PORT{-15};

constexpr int INERTIAL_SENSOR_PORT{16};

#define LEFT_WINGS_PORT 'F'
#define RIGHT_WINGS_PORT 'B'
#define BACK_WINGS_PORT 'H'
#define LEFT_HANG_PORT 'C'
#define RIGHT_HANG_PORT 'D'

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

pros::ADIDigitalOut right_wings(RIGHT_WINGS_PORT); // wing mechanism piston
pros::ADIDigitalOut left_wings(LEFT_WINGS_PORT);                                                
pros::ADIDigitalOut back_wings(BACK_WINGS_PORT); // wing mechanism piston
pros::ADIDigitalOut left_hang_piston(LEFT_HANG_PORT);        // hang piston
pros::ADIDigitalOut right_hang_piston(RIGHT_HANG_PORT);        // hang piston
// Define sensors:

pros::Imu inertial_sensor(INERTIAL_SENSOR_PORT); // inertial sensor

Drive easy(
    {LEFT_FRONT_PORT, LEFT_MIDDLE_PORT,LEFT_BACK_PORT}
    ,
    {RIGHT_FRONT_PORT, RIGHT_MIDDLE_PORT, RIGHT_BACK_PORT}
    ,
    INERTIAL_SENSOR_PORT
    ,
    3.25
    ,
    600
    ,
    1.333
);

// ANCHOR Chassis class
lemlib::Drivetrain drivetrain{
    &left_motors,  // left drivetrain motors
    &right_motors, // right drivetrain motors
    11.000,         // track width
    3.25,          // wheel diameter
    450,           // wheel rpm
    1.5              // chase power
};

lemlib::OdomSensors sensors{nullptr, nullptr, nullptr, nullptr,
                            &inertial_sensor};

lemlib::ControllerSettings lateralController{
    10,  // kp
    0,   // ki
    20,  // kd
    0,   // windup range
    1,   // small error range
    100, // small timeout
    3,   // big error range
    500, // big error timeout
    20    // slew
};

lemlib::ControllerSettings angularController{
    2.3,   // kp
    0.3, // ki
    13.5,  // kd
    5,  // windup range
    1,   // small error range
    50,  // small timeout
    3,   // big error range
    500, // big error timeout
    0    // slew
};

lemlib::MoveToPoseParams moveToPoseParams{
  true, 0, 0.6, 127, 0, 0
};

lemlib::Chassis lem(drivetrain, lateralController, angularController,
                        sensors);


// ANCHOR catapult control
void catapult::lower() { // catapult reset function
  while ((int)shooter.get_position() % 180 < 145 ) {   // executes while catapult is not at the desired angle
    shooter = 100; // outputs power to the catapult motor
    pros::delay(10);
  }
  shooter.brake(); // stops the catapult motor
  state = 2;       // sets the state to "loaded"
}

// ANCHOR async cata implementation
void catapult::control() {
  shooter.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
  shooter.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  shooter = 0;
  while (true) {
    
    if ((int) shooter.get_position() % 180 < 140 && cata.state != 1 && cata.state != 3) // checks if the catapult should be lowered
    {
      cata.state = 1;
      cata.lower();
    }
    
    if (cata.state == 3) // if cata is set to continuous
    {
      shooter = 115;
    }
    pros::delay(15);
  }
}

catapult cata; // creates an instance of the catapult object
