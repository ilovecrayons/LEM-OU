#include "config.hpp"
#include "main.h"
#include "pros/rtos.hpp"

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
  easy.set_exit_condition(easy.swing_exit, 50, 1, 250, 3, 250, 500);
  easy.set_exit_condition(easy.drive_exit, 35, 2, 150, 4, 250, 500);
}
/*
void ez_defaults(){
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);

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
  lem.turnTo(-30, -61, 1000);
  lem.waitUntilDone();
  lem.moveToPoint(-30, -61, 3000, true);
  lem.turnTo(-8, -61, 1000);
  lem.waitUntilDone();
  pros::delay(6000);
  lem.moveToPoint(-11.2, -61, 3000, true);
}

void closeDisrupt() {
  lem.setPose(-35, -55.4, 0);
  intake = -120;
  front_wings.set_value(true);
  lem.moveToPoint(-24.994, -11.075, 2000);
  lem.waitUntil(45);
  front_wings.set_value(false);
  lem.moveToPoint(-27, -13.5, 2000, false);
  lem.waitUntilDone();
  lem.turnTo(-5.8, -12, 2000);
  lem.waitUntilDone();
  front_wings.set_value(true);
  lem.moveToPoint(-3, -12, 2000);
  lem.waitUntilDone();
  front_wings.set_value(false);
  lem.turnTo(-54, -56, 2000, false);
  lem.moveToPoint(-48, -51, 2000, false, 80);
  lem.waitUntilDone();
  lem.turnTo(20, -80, 2000);
  lem.waitUntilDone();

  intake = 120;
}

void skills() {
  intake = -120;
  lem.setPose(-38, -58, 90);
  lem.turnTo(-56, -41, 2000, false);
  lem.moveToPoint(-56, -41, 2000, false);
  lem.turnTo(46, -3, 2000);
  lem.waitUntilDone();
  back_wings.set_value(true);
  cata.state = 3;
  pros::delay(24000);
  cata.state = 0;
  back_wings.set_value(false);
  lem.turnTo(-58, -30, 2000, false);
  lem.moveToPoint(-56, -26, 2000, false);
  lem.moveToPoint(-56, -41, 2000);
  lem.turnTo(-38, -59.5, 2000, false);
  lem.moveToPoint(-38, -59.5, 2000, false);
  lem.turnTo(39, -59.5, 2000, false);
  lem.moveToPoint(39, -59.5, 2000, false);
  lem.turnTo(63, -43, 2000, false);
  lem.moveToPoint(63, -43, 2000, false);
  lem.turnTo(63, -29, 2000, false);
  lem.moveToPoint(63, -28.582, 2000, false);
  lem.moveToPoint(63, -45.478, 2000);
  lem.turnTo(15.328, -29.714, 2000);
  lem.moveToPoint(15.328, -29.714, 2000);
  lem.turnTo(15.725, -22, 2000);
  lem.moveToPoint(15.725, -22, 2000);
  lem.turnTo(39.126, -22, 2000, false);
  lem.moveToPoint(39.126, -22, 2000, false);
  lem.moveToPoint(13.725, -22, 2000);

  lem.turnTo(13, 0, 2000);
  lem.moveToPoint(13, 0, 2000);
  lem.turnTo(39, 0, 2000, false);
  back_wings.set_value(true);
  lem.moveToPoint(39, 0, 2000, false);
  lem.moveToPoint(11, 0, 2000);
  lem.waitUntil(5);
  back_wings.set_value(false);
  lem.turnTo(11, 25, 2000);
  lem.moveToPoint(11, 25, 2000);
  lem.turnTo(40, 5, 2000, false);
  lem.moveToPoint(50, 5, 2000, false);
  back_wings.set_value(true);
  lem.moveToPoint(13, 25, 2000);
  lem.waitUntil(5);
  back_wings.set_value(false);
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
  easy.set_drive_pid(-37, 80);
  easy.wait_drive();
  easy.set_swing_pid(ez::LEFT_SWING, -45, 120);
  easy.wait_drive();
  back_wings.set_value(true);
  easy.set_drive_pid(-10, 120);
  easy.wait_drive();
  back_wings.set_value(false);
  easy.set_swing_pid(ez::LEFT_SWING, -87, 120);
  easy.wait_drive();
  

  easy.set_drive_pid(-17, 120);
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
  easy.set_turn_pid(-343, 120);
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
  front_wings.set_value(true);
  easy.set_drive_pid(30, 120);
  intake = 120;
  easy.wait_drive();
  front_wings.set_value(false);
  easy.set_drive_pid(-10, 120);

}

void driverStart() {
  intake = -120;
  lem.setPose(-38, -58, 90);
  lem.turnTo(-56, -41, 2000, false);
  lem.moveToPoint(-56, -41, 2000, false);
  lem.turnTo(46, -3, 2000);
  lem.waitUntilDone();
  back_wings.set_value(true);
  cata.state = 3;
}
