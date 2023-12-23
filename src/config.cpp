#include "config.hpp"
#include "main.h"

//ANCHOR device port configuration

constexpr int LEFT_FRONT_PORT {-1};
constexpr int LEFT_MIDDLE_PORT {-2};
constexpr int LEFT_BACK_PORT {-3};
constexpr int RIGHT_FRONT_PORT {17};
constexpr int RIGHT_MIDDLE_PORT {5};
constexpr int RIGHT_BACK_PORT {6};

constexpr int INTAKE_PORT {-14};
constexpr int SHOOTER_PORT {-12};

constexpr int CATA_ROT_PORT {8};
constexpr int LIFT_ROT_PORT {20};
constexpr int INERTIAL_SENSOR_PORT {11};

#define LEFT_WING_PORT 'A'
#define RIGHT_WING_PORT 'B'
#define PTO_PORT 'C'
#define RATCHET_PORT 'D'
#define HOOK_PORT 'E'

// ANCHOR Robot setup 

pros::Controller master(CONTROLLER_MASTER);

// Defines motors:

pros::Motor left_front_motor(LEFT_FRONT_PORT, pros::E_MOTOR_GEAR_BLUE);      // blue cartridge, 11W
pros::Motor left_middle_motor(LEFT_MIDDLE_PORT, pros::E_MOTOR_GEARSET_06);   // blue cartridge, 11W
pros::Motor left_back_motor(LEFT_BACK_PORT, pros::E_MOTOR_GEAR_BLUE);        // blue cartridge, 11W
pros::Motor right_front_motor(RIGHT_FRONT_PORT, pros::E_MOTOR_GEAR_BLUE);    // blue cartridge, 11W
pros::Motor right_middle_motor(RIGHT_MIDDLE_PORT, pros::E_MOTOR_GEARSET_06); // blue cartridge, 11W
pros::Motor right_back_motor(RIGHT_BACK_PORT, pros::E_MOTOR_GEAR_BLUE);      // blue cartridge, 11W

pros::MotorGroup left_motors({left_front_motor, left_middle_motor, left_back_motor});
pros::MotorGroup right_motors({right_front_motor, right_middle_motor, right_back_motor});

pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEAR_BLUE);  // blue cartridge, 11W
pros::Motor shooter(SHOOTER_PORT, pros::E_MOTOR_GEAR_RED); // red cartridge, 11W

// Define pneumatics:

pros::ADIDigitalOut left_wing(LEFT_WING_PORT);   // wing mechanism piston
pros::ADIDigitalOut right_wing(RIGHT_WING_PORT); // wing mechanism piston
pros::ADIDigitalOut pto_piston(PTO_PORT);        // pto piston
pros::ADIDigitalOut hook(HOOK_PORT);             // hook piston
pros::ADIDigitalOut ratchet(RATCHET_PORT);       // ratchet piston

// Define sensors:

pros::Rotation cata_rot(CATA_ROT_PORT, true);  // catapult rotation sensor
pros::Rotation lift_rot(LIFT_ROT_PORT, false); // lift rotation sensor
pros::Imu inertial_sensor(INERTIAL_SENSOR_PORT); // inertial sensor

// ANCHOR Chassis class
lemlib::Drivetrain drivetrain{
    &left_motors, // left drivetrain motors
    &right_motors, // right drivetrain motors
    10, // track width
    3.25, // wheel diameter
    360, // wheel rpm
    1 // chase power
};

lemlib::OdomSensors sensors{
    nullptr, 
    nullptr,
    nullptr,
    nullptr,
    &inertial_sensor
};

lemlib::ControllerSettings lateralController{
    1, //kp
    0, //ki
    1, //kd
    0, //windup range
    1, //small error range
    100, //small timeout 
    3, //big error range
    500, //big error timeout
    5 //slew
};

lemlib::ControllerSettings angularController{
    4, //kp
    0, //ki
    40, //kd
    0, //windup range
    1, //small error range
    100, //small timeout 
    3, //big error range
    500, //big error timeout
    40 //slew
};

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);


/**
 * ANCHOR toggle pto procedure
 * @param bool toggle
 * sets the pto state with given parameter
*/
void ptoClass::set_pto(bool toggle) 
{
    pto_enable = toggle; //sets the global state variable to the desired state

    if (toggle) // if the pto is desired to be raised
    {
        
        pto_piston.set_value(toggle); // actuate both pto pistons
        left_motors[2] = 30; // spin pto motors to allow gear mesh
        right_motors[2] = 30;
        pros::delay(200);
        left_motors[2] = 0;
        right_motors[2] = 0;
        right_motors[2].set_brake_mode(E_MOTOR_BRAKE_HOLD); // sets both motors to hold
        left_motors[2].set_brake_mode(E_MOTOR_BRAKE_HOLD);
        while (lift_rot.get_position() < 9900 && !pto_override) // continuously spins motors until the pto is raised to 99 degrees
        {
            left_motors[2] = 120;
            right_motors[2] = 120;
        }
        right_motors[2] = 0;
        left_motors[2] = 0;
    } else if (!toggle){ // if the pto is desired to be lowerd
        right_motors[2].set_brake_mode(E_MOTOR_BRAKE_HOLD); // disable hold from both motors
        left_motors[2].set_brake_mode(E_MOTOR_BRAKE_HOLD);
        while (lift_rot.get_position() > 500 && !pto_override){ //continuously spins the pto motors in reverse until thje pto is lowered to 15 degrees
            left_motors[2] = -120;
            right_motors[2] = -120;
        }
        right_motors[2] = 0;
        left_motors[2] = 0;
        if(!pto_override){
            pto_piston.set_value(toggle); // shift the pto pistons back to drive state
            right_motors[2].set_brake_mode(E_MOTOR_BRAKE_COAST); // disable hold from both motors
            left_motors[2].set_brake_mode(E_MOTOR_BRAKE_COAST);
            left_motors[2] = -30; // spin both pto motors to mesh with drive
            right_motors[2] = -30;
        }
        
        pros::delay(200);
        right_motors[2] = 0;
        left_motors[2] = 0;
        

    }
    master.rumble("-"); // vibrates the controller to signal the driver that the state change has finished
}

// ANCHOR catapult control
void catapult::lower()
{ // catapult reset function
    while (cata_rot.get_position() < 4000)
    {                  // executes while catapult is not at the desired angle
        shooter = 127; // outputs power to the catapult motor
        pros::delay(10);
    }
    shooter.brake(); // stops the catapult motor
    state = 2;       // sets the state to "loaded"
}

// ANCHOR async cata implementation
void control() {
  shooter.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  while (true) {
    if (cata_rot.get_position() < 1000 && cata.state != 1 && cata.state != 3) // checks if the catapult should be lowered
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
ptoClass pto;  // creates an instance of the pto object