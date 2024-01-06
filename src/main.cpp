#include "main.h"
#include "config.hpp"
#include "autons.hpp"


// ANCHOR runtime variables
double fwd;
double turning;
float up;
float down;
bool hooked = false;
bool ratcheted = false;
bool lifted = false;



void sv() {
  // loop forever
  while (true) {
    lemlib::Pose pose =
        chassis.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f", pose.x);           // print the x position
    pros::lcd::print(1, "y: %f", pose.y);           // print the y position
    pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
    pros::delay(10);
  }
}

void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  cata_rot.reset_position();
  lift_rot.reset_position();
  pros::Task continuous{[=] { // creates a lambda task for catapult control
    cata.control();
  }};
  chassis.setPose(-47, -58, 0);
  pros::Task sophieVang(sv);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  close();
  
  
}
// ANCHOR opcontrol curve implementation
void arcadeCurve(pros::controller_analog_e_t power,
                 pros::controller_analog_e_t turn, pros::Controller mast,
                 float t) {
  up = mast.get_analog(power);
  down = mast.get_analog(turn);

  fwd = (exp(-t / 10) + exp((fabs(up) - 127) / 10) * (1 - exp(-t / 10))) * up;
  turning = -1 * down;
  if (pto.pto_enable) {
    left_motors[0] = (fwd - turning);
    left_motors[1] = (fwd - turning);
    right_motors[0] = (fwd + turning);
    right_motors[1] = (fwd + turning);

  } else {
    left_motors = (fwd - turning);
    right_motors = (fwd + turning);
  }
}

// ANCHOR opctrl
void opcontrol() {
  while (true) { // calls the arcade drive function
    arcadeCurve(pros::E_CONTROLLER_ANALOG_LEFT_Y,
                pros::E_CONTROLLER_ANALOG_RIGHT_X, master, 10);

    // intake
    if (master.get_digital(DIGITAL_L1)) // intake
    {
      intake = 120;
    }
    if (master.get_digital(DIGITAL_L2)) // outtake
    {
      intake = -120;
    }
    if (master.get_digital(DIGITAL_L1) == false &&
        master.get_digital(DIGITAL_L2) == false) // stop intake
    {
      intake = 0;
    }

    // wing
    if (master.get_digital(DIGITAL_R1)) // wing retract
    {
      left_wing.set_value(true);
      right_wing.set_value(true);
    } else if (!master.get_digital(DIGITAL_R1)) // wing expand
    {
      right_wing.set_value(false);
      left_wing.set_value(false);
    }

    // catapult
    if (cata.state != 3 && master.get_digital(DIGITAL_B)) // continuous launch
    {
      cata.state = 3;
      pros::delay(500);
    }
    // catapult
    if (cata.state == 3 && master.get_digital(DIGITAL_B)) // continuous launch
    {
      cata.state = 0;
      pros::delay(500);
    }

    // hook mechanism
    if (master.get_digital(DIGITAL_X)) {
      hooked = !hooked;
      pros::delay(200);
    }
    if (hooked) {
      hook.set_value(true);
    }
    if (!hooked) {
      hook.set_value(false);
    }

    // pto lift mechanism
    if (master.get_digital(DIGITAL_RIGHT)) {
      lifted = !lifted;
      pros::Task engagePto{[=] { // creates a lambda task for the pto
        pto.set_pto(lifted);
      }};
      pros::delay(500);
    }

    // pto manual override
    if (master.get_digital(DIGITAL_UP) || master.get_digital(DIGITAL_DOWN)) {
      pto.pto_override = true;
    }
    if (master.get_digital(DIGITAL_UP)) {
      left_motors[2] = 127;
      right_motors[2] = 127;
    } else if (master.get_digital(DIGITAL_DOWN)) {
      left_motors[2] = -127;
      right_motors[2] = -127;
    }
    if (pto.pto_override == true && !master.get_digital(DIGITAL_DOWN) &&
        !master.get_digital(DIGITAL_UP)) {
      left_motors[2] = 0;
      right_motors[2] = 0;
      pto.pto_override = false;
    }

    // rachet mechanism
    if (master.get_digital(DIGITAL_LEFT)) {
      ratcheted = !ratcheted;
      pros::delay(300);
    }
    if (ratcheted) {
      ratchet.set_value(true);
    }
    if (!ratcheted) {
      ratchet.set_value(false);
    }

    pros::delay(20);
  }
}
