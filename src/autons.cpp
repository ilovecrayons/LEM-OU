#include "EZ-Template/util.hpp"
#include "config.hpp"
#include "main.h"
#include "pros/rtos.hpp"

namespace vang {
void fuckdavidlin() {}
} // namespace vang

constexpr int EARLY_EXIT{0};
constexpr int MIN_SPEED{0};
ASSET(closesafe1_txt)
ASSET(closedisrupt_txt)

void default_constants() {
  easy.set_slew_min_power(80, 80);
  easy.set_slew_distance(7, 7);
  easy.set_pid_constants(&easy.headingPID, 12, 0, 20, 0);
  easy.set_pid_constants(&easy.forward_drivePID, 0.5, 0, 4, 0);
  easy.set_pid_constants(&easy.backward_drivePID, 0.5, 0, 4, 0);
  easy.set_pid_constants(&easy.turnPID, 5, 0.003, 47, 15);
  easy.set_pid_constants(&easy.swingPID, 7, 0, 50, 0);
}

void exit_condition_defaults() {
  easy.set_exit_condition(easy.turn_exit, 35, 1, 150, 3, 250, 500);
  easy.set_exit_condition(easy.swing_exit, 50, 2, 250, 5, 250, 500);
  easy.set_exit_condition(easy.drive_exit, 35, 30, 150, 150, 250, 500);
}
/*
void ez_defaults(){
  easy.set_slew_min_power(80, 80);
  easy.set_slew_distance(7, 7);
  easy.set_pid_constants(&easy.headingPID, 11, 0, 20, 0);
  easy.set_pid_constants(&easy.forward_drivePID, 0.45, 0, 5, 0);
  easy.set_pid_constants(&easy.backward_drivePID, 0.45, 0, 5, 0);
  easy.set_pid_constants(&easy.turnPID, 5, 0.003, 35, 15);
  easy.set_pid_constants(&easy.swingPID, 7, 0, 45, 0);

}
*/
void closeSafe() {
  lem.setPose(-46.451, -57.626, 135);
  intake = -120;
  pros::delay(2000);
  back_wings.set_value(true);
  pros::delay(500);
  intake = 120;
  lem.turnTo(-55, -9, 1000);
  lem.waitUntil(45);
  back_wings.set_value(false);
  lem.turnTo(-30, -65, 1000);
  lem.waitUntilDone();
  lem.moveToPoint(-30, -65, 3000, true);
  lem.turnTo(-9, -65, 1000);
  lem.waitUntilDone();
  pros::delay(6000);
  lem.moveToPoint(-10, -65, 3000, true);
}

void closeDisrupt() {
  lem.setPose(-35, -55.4, 0);
  intake = -120;
  right_wings.set_value(true);
  lem.moveToPoint(-24.994, -11.075, 2000);
  lem.waitUntil(45);
  right_wings.set_value(false);
  lem.moveToPoint(-27, -13.5, 2000, false);
  lem.waitUntilDone();
  lem.turnTo(-5.8, -12, 2000);
  lem.waitUntilDone();
  right_wings.set_value(true);
  lem.moveToPoint(-3, -12, 2000);
  lem.waitUntilDone();
  right_wings.set_value(false);
  lem.turnTo(-54, -56, 2000, false);
  lem.moveToPoint(-48, -51, 2000, false, 80);
  lem.waitUntilDone();
  lem.turnTo(20, -80, 2000);
  lem.waitUntilDone();

  intake = 120;
}

void skills() {
  intake = -120;
  easy.set_turn_pid(45, 120);
  easy.wait_drive();
  easy.set_drive_pid(-28, 120);
  easy.wait_drive();
  easy.set_turn_pid(-19.5, 120);
  easy.wait_drive();
  back_wings.set_value(true);
  cata.state = 3;
  intake = 0;
  // pros::delay(31700);
  back_wings.set_value(false);
  pros::delay(300);
  cata.state = 0;
  easy.set_turn_pid(45, 120);
  easy.wait_drive();
  easy.set_swing_pid(ez::RIGHT_SWING, 90, 120);
  easy.wait_drive();
  easy.set_mode(ez::DISABLE);
  easy.set_tank(-127, -127);
  pros::delay(500);
  easy.set_tank(0, 0);
  easy.set_mode(ez::DRIVE);

  easy.set_turn_pid(45, 120);
  easy.wait_drive();
  easy.set_drive_pid(35, 120);
  easy.wait_drive();
  easy.set_turn_pid(0, 100);
  easy.wait_drive();
  intake = 120;
  easy.set_drive_pid(80, 120);
  easy.wait_drive();
  easy.set_swing_pid(ez::RIGHT_SWING, -45, 120);
  right_wings.set_value(true);
  left_wings.set_value(true);
  easy.wait_drive();
  easy.set_drive_pid(23, 120);
  easy.wait_until(10);
  right_wings.set_value(false);
  left_wings.set_value(false);
  easy.wait_drive();

  
  easy.set_swing_pid(ez::RIGHT_SWING, -90, 120);
  easy.wait_drive();
  easy.set_mode(ez::DISABLE);
  easy.set_tank(127, 127);
  pros::delay(500);
  easy.set_tank(0, -0);
  easy.set_mode(ez::DRIVE);
  easy.set_drive_pid(-6, 120);
  easy.wait_drive();
  easy.set_mode(ez::DISABLE);
  easy.set_tank(127, 127);
  pros::delay(500);
  easy.set_tank(0, -0);
  easy.set_mode(ez::DRIVE);
  easy.set_drive_pid(-5, 120);
  easy.wait_drive();
  easy.set_turn_pid(0, 120);
  easy.wait_drive();
  easy.set_drive_pid(-26, 120);
  easy.wait_drive();
  easy.set_turn_pid(-90, 120);
  easy.wait_drive();
  left_wings.set_value(true);
  right_wings.set_value(true);
  easy.set_drive_pid(18, 120);
  easy.wait_drive();
  easy.set_drive_pid(-18, 120);
  easy.wait_drive();
  left_wings.set_value(false);
  right_wings.set_value(false);
  easy.set_turn_pid(70, 120);
  easy.wait_drive();
  easy.set_drive_pid(-19, 120);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, 0, 120);
  right_wings.set_value(true);
  easy.wait_drive();
  easy.set_drive_pid(31, 80);
  intake = 120;
  easy.wait_drive();
  easy.set_drive_pid(-32, 120);
  easy.wait_drive();
  easy.set_turn_pid(-90, 120);
  easy.wait_until(-70);
  right_wings.set_value(true);
  left_wings.set_value(true);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, 0, 120);
  easy.wait_drive();
  intake = 120;
  left_wings.set_value(false);
  easy.set_drive_pid(30, 80);
  easy.wait_drive();
  easy.set_drive_pid(-32, 120);
  easy.wait_drive();
  easy.set_turn_pid(-90, 120);
  easy.wait_until(-70);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, 0, 120);
  easy.wait_drive();
  left_wings.set_value(false);
  easy.set_drive_pid(30, 80);
  easy.wait_drive();
  easy.set_drive_pid(-29, 120);
  easy.wait_drive();
  easy.set_turn_pid(-90, 120);
  easy.wait_until(-80);
  left_wings.set_value(true);
  intake = 120;
  easy.set_drive_pid(15, 120);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, 10, 120);
  easy.wait_drive();
  easy.set_swing_pid(ez::RIGHT_SWING, -65, 120);
  easy.wait_drive();

  easy.set_drive_pid(15, 120);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, 45, 120);
  easy.wait_drive();
  easy.set_drive_pid(15, 120);
  easy.wait_until(-10);
  left_wings.set_value(false);
  right_wings.set_value(false);
  

  easy.set_swing_pid(ez::LEFT_SWING, 80, 120);
  easy.wait_drive();
  easy.set_mode(ez::DISABLE);
  easy.set_tank(127, 127);
  pros::delay(500);
  easy.set_tank(0, -0);
  easy.set_mode(ez::DRIVE);
  easy.set_drive_pid(-6, 120);
  easy.wait_drive();
  easy.set_mode(ez::DISABLE);
  easy.set_tank(127, 127);
  pros::delay(500);
  easy.set_tank(0, -0);
  easy.set_mode(ez::DRIVE);
  easy.set_swing_pid(ez::LEFT_SWING, 50, 120);
  easy.wait_drive();
  easy.set_drive_pid(-32, 120);
  easy.wait_drive();
  easy.set_turn_pid(-180, 120);
  easy.wait_drive();
  easy.set_mode(ez::DISABLE);
  easy.set_tank(127, 127);
  pros::delay(2000);
  easy.set_tank(0, 0);
  // easy.set_drive_pid(14, 120);
  // easy.wait_drive();
  // easy.set_turn_pid(-80, 120);
  // easy.wait_drive();
  // easy.mode = ez::DISABLE;
  // easy.set_tank(-127, -127);
  // pros::delay(2000);
  // easy.set_tank(0, 0);
  // easy.mode = ez::DRIVE;
  // easy.set_drive_pid(13, 120);
  // easy.wait_drive();
  // easy.set_turn_pid(0, 120);
  // easy.wait_drive();
  // easy.set_drive_pid(13, 120);
  // easy.wait_drive();
  // easy.set_turn_pid(50, 120);
  // easy.wait_drive();
  // back_wings.set_value(true);
  // easy.set_drive_pid(20, 120);
  // easy.wait_drive();
  // back_wings.set_value(false);
  // easy.set_turn_pid(0, 120);
  // easy.wait_drive();
  // easy.set_drive_pid(23, 120);
  // easy.wait_drive();
  // easy.set_turn_pid(90, 120);
  // easy.wait_drive();
  // easy.set_drive_pid(30, 120);
  // easy.wait_drive();
  // easy.set_swing_pid(ez::LEFT_SWING, 180, 120);
  // easy.wait_drive();
  // back_wings.set_value(true);
}

void trustAlliance() {
  /*
  lem.setPose(0, 0, 0);
  lem.moveToPoint(0, 24, 5000);
  lem.waitUntilDone();
  lem.moveToPoint(0, 0, 5000, false);
  lem.waitUntilDone();


  lem.turnTo(45, 45, 5000);
  lem.turnTo(-45, -45, 5000);
  lem.turnTo(0, 10, 5000);
  lem.turnTo(45, 45, 5000);
  lem.turnTo(-45, -45, 5000);
  lem.turnTo(0, 10, 5000);
  */
}

void farSafe() {
  intake = -120;
  easy.set_drive_pid(6, 100);
  easy.wait_drive();
  easy.set_drive_pid(-33, 80);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, -45, 120);
  easy.wait_drive();
  back_wings.set_value(true);
  easy.set_drive_pid(-10, 120);
  easy.wait_drive();
  back_wings.set_value(false);
  easy.set_swing_pid(ez::LEFT_SWING, -87, 120);
  easy.wait_drive();

  easy.set_drive_pid(-15, 120);
  easy.wait_drive();
  easy.set_drive_pid(10, 120);
  easy.wait_drive();
  easy.set_turn_pid(-267, 120);
  easy.wait_drive();
  intake = 120;
  easy.set_drive_pid(15, 120);
  easy.wait_drive();
  easy.set_drive_pid(-15, 120);
  easy.wait_drive();
  easy.set_turn_pid(-325, 120);
  easy.wait_drive();
  intake = -120;
  easy.set_drive_pid(48.5, 120);
  easy.wait_drive();
  easy.set_turn_pid(-210, 120);
  easy.wait_drive();
  easy.set_drive_pid(20, 120);
  intake = 120;
  easy.wait_drive();
  easy.set_turn_pid(-330, 120);
  easy.wait_drive();
  easy.set_drive_pid(26, 120);
  intake = -120;
  easy.wait_drive();
  easy.set_turn_pid(-180, 120);
  easy.wait_drive();
  right_wings.set_value(true);
  easy.set_drive_pid(30, 120);
  intake = 120;
  easy.wait_drive();
  right_wings.set_value(false);
  easy.set_drive_pid(-10, 120);
}

void driverStart() {

  lem.setPose(-38, -58, 90);
  lem.turnTo(-56, -40, 2000, false);
  lem.moveToPoint(-56, -40, 2000, false);
  lem.turnTo(46, 3, 2000);
  lem.waitUntilDone();
  back_wings.set_value(true);
  cata.state = 3;
}
