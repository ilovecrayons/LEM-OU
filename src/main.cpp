#include "main.h"
#include "autons.hpp"
#include "config.hpp"

// ANCHOR runtime variables
double fwd;
double turning;
float up;
float down;
bool lifted = true;
int autoSelector = 3;

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
  hang_piston.set_value(true);
  pros::lcd::initialize();
  chassis.calibrate();
  pros::Task continuous{[=] { // creates a lambda task for catapult control
    cata.control();
  }};
  pros::Task sophieVang(sv);
}

void disabled() {
  while (true) {
    if (bumper.get_value() == 1) {
      autoSelector++;
      pros::delay(500);
    }
    if (autoSelector > 3) {
      autoSelector = 0;
    }
    pros::delay(20);
    switch (autoSelector) {
    case 0:
      pros::lcd::print(5, "Close Safe");
      break;
    case 1:
      pros::lcd::print(5, "Close Disrupt");
      break;
    case 2:
      pros::lcd::print(5, "Skills");
      break;
    case 3:
      pros::lcd::print(5, "Trust Alliance");
      break;
    }
  }
}

void competition_initialize() {
  while (true) {
    if (bumper.get_value() == 1) {
      autoSelector++;
      pros::delay(500);
    }
    if (autoSelector > 3) {
      autoSelector = 0;
    }
    pros::delay(20);
    switch (autoSelector) {
    case 0:
      pros::lcd::print(5, "Close Safe");
      break;
    case 1:
      pros::lcd::print(5, "Close Disrupt");
      break;
    case 2:
      pros::lcd::print(5, "Skills");
      break;
    case 3:
      pros::lcd::print(5, "Trust Alliance");
      break;
    }
  }
}

void autonomous() {
  switch (autoSelector) {
  case 0:
    pros::lcd::print(5, "Close Safe");
    closeSafe();
    break;
  case 1:
    pros::lcd::print(5, "Close Disrupt");
    closeDisrupt();
    break;
  case 2:
    pros::lcd::print(5, "Skills");
    skills();
    break;
  case 3:
    pros::lcd::print(5, "Trust Alliance");
    trustAlliance();
    break;
  }
}
// ANCHOR opcontrol curve implementation
void arcadeCurve(pros::controller_analog_e_t power,
                 pros::controller_analog_e_t turn, pros::Controller mast,
                 float t) {
  up = mast.get_analog(power);
  down = mast.get_analog(turn);
  fwd = (exp(-t / 10) + exp((fabs(up) - 127) / 10) * (1 - exp(-t / 10))) * up;
  turning = -1 * down;
  left_motors = (fwd - turning);
  right_motors = (fwd + turning);
}

// ANCHOR opctrl
void opcontrol() {
  while (true) { // calls the arcade drive function
    arcadeCurve(pros::E_CONTROLLER_ANALOG_LEFT_Y,
                pros::E_CONTROLLER_ANALOG_RIGHT_X, master, 15);

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
      front_wings.set_value(true);
    } else if (!master.get_digital(DIGITAL_R1)) // wing expand
    {
      front_wings.set_value(true);
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

    // hang mechanism
    if (master.get_digital(DIGITAL_RIGHT)) {
      lifted = !lifted;
      pros::delay(300);
    }
    if (lifted) {
      hang_piston.set_value(true);
    }
    if (!lifted) {
      hang_piston.set_value(false);
    }

    pros::delay(20);
  }
}
