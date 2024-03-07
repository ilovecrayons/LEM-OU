#include "main.h"
#include "autons.hpp"
#include "config.hpp"

// ANCHOR runtime variables
double fwd;
double turning;
float up;
float down;
bool lifted = false;
int autoSelector = 0;

void sv() {
  // loop forever
  while (true) {
    lemlib::Pose pose =
        lem.getPose(); // get the current position of the robot
    pros::lcd::print(0, "x: %f", pose.x);           // print the x position
    pros::lcd::print(1, "y: %f", pose.y);           // print the y position
    pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
    pros::delay(10);
  }
}

void autonSelector() {

  autoSelector++;

  if (autoSelector > 5) {
    autoSelector = 0;
  }
}

void initializeInstance() {
  if (autoSelector == 0 || autoSelector == 1 || autoSelector == 5) {
    pros::delay(500);
    lem.calibrate();
    pros::Task sophieVang(sv);
  } else {
    pros::delay(500);
    easy.initialize();
    easy.reset_pid_targets();  // Resets PID targets to 0
    easy.reset_gyro();         // Reset gyro position to 0
    easy.reset_drive_sensor(); // Reset drive sensors to 0
    easy.set_drive_brake(MOTOR_BRAKE_HOLD);
    easy.toggle_modify_curve_with_controller(false);
    easy.set_active_brake(0);
    easy.set_curve_default(0, 0);
    pros::lcd::print(4, "initialized");
    exit_condition_defaults();
  }
}

void callSelectedAuton() {
  while (true) {
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
    case 4:
      pros::lcd::print(5, "far safe");
      break;
    case 5:
      pros::lcd::print(5, "david lin driver skill issue");
      break;
    }
    pros::delay(20);
  }
}

void initialize() {
  if(autoSelector == 2);
    ///easy.initialize();
  pros::lcd::initialize();
  pros::lcd::register_btn1_cb(autonSelector);
  pros::lcd::register_btn2_cb(initializeInstance);
  pros::Task continuous{[=] { // creates a lambda task for catapult control
    cata.control();
  }};

}

void disabled() {
  left_hang_piston.set_value(false);
  right_hang_piston.set_value(false);
  callSelectedAuton();
}

void competition_initialize() { callSelectedAuton(); }

void autonomous() {
  switch (autoSelector) {
  case 0:
    pros::lcd::print(5, "Close Safe");
    closeSafe();
    break;
  case 1:
    pros::lcd::print(5, "Close Disrupt");
    closeDisrupt();
    easy.set_drive_brake(MOTOR_BRAKE_COAST);
    break;
  case 2:
    pros::lcd::print(5, "Skills");
    skills();
    easy.set_drive_brake(MOTOR_BRAKE_COAST);
    break;
  case 3:
    pros::lcd::print(5, "Trust Alliance");
    trustAlliance();
    easy.set_drive_brake(MOTOR_BRAKE_COAST);
    break;
  case 4:
    pros::lcd::print(5, "far safe");
    farSafe();
    easy.set_drive_brake(MOTOR_BRAKE_COAST);
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

void timer() {
  pros::delay(75000);
  master.rumble("-.-.-");
  pros::delay(10000);
  master.rumble("-.-");
  pros::delay(10000);
  master.rumble("...");
}

// ANCHOR opctrl
void opcontrol() {
  pros::Task timerTask(timer);
  if (autoSelector == 5) {
    driverStart();
    while (!master.get_digital(DIGITAL_B))
      ;
    
  }
  if (autoSelector != 0)
    easy.set_drive_brake(MOTOR_BRAKE_COAST);
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
    if (master.get_digital(DIGITAL_R1)) // wing expand
    {
      right_wings.set_value(true);
      left_wings.set_value(true);
    } else if (!master.get_digital(DIGITAL_R1)) // wing retract
    {
      right_wings.set_value(false);
      left_wings.set_value(false);
    }

    if (master.get_digital(DIGITAL_R2)) // wing expand
    {
      back_wings.set_value(true);
    } else if (!master.get_digital(DIGITAL_R2)) // wing retract
    {
      back_wings.set_value(false);
    }

    // catapult
    if (cata.state != 3 && master.get_digital(DIGITAL_B)) // continuous launch
    {
      cata.state = 3;
      pros::delay(300);
    }
    // catapult
    if (cata.state == 3 && master.get_digital(DIGITAL_B)) // continuous launch
    {
      cata.state = 0;
      pros::delay(300);
    }

    // hang mechanism
    if (master.get_digital(DIGITAL_RIGHT)) {
      lifted = !lifted;
      pros::delay(300);
    }
    if (lifted) {
      left_hang_piston.set_value(true);
      right_hang_piston.set_value(true);
    }
    if (!lifted) {
      right_hang_piston.set_value(false);
      left_hang_piston.set_value(false);
    }

    pros::delay(20);
  }
}
