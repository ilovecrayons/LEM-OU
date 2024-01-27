#include "main.h"
#include "config.hpp"
#include "pros/rtos.hpp"

constexpr int EARLY_EXIT{0};
constexpr int MIN_SPEED{0};

ASSET(closesafe1_txt)
ASSET(closedisrupt_txt)
void closeSafe() {
  chassis.setPose(-46.451, -57.626, 135);
  hang_piston.set_value(true);
  back_wings.set_value(true);
  pros::delay(500);
  intake = 120;
  chassis.turnTo(-8, -60, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-9, -60, 3000, true);
  chassis.waitUntil(8);
  back_wings.set_value(false);

}

void closeDisrupt() {
  
  chassis.setPose(-35, -55.4, 0);
  hang_piston.set_value(true);
  //chassis.turnTo(-25.994, -9, 1000);
  chassis.moveToPoint(-25.994, -14.075, 2000);
  intake = -120;
  chassis.waitUntilDone();
  chassis.moveToPoint(-25, -12, 2000, false);
  chassis.waitUntilDone();
  chassis.turnTo(-5.8, -12, 2000);
  chassis.waitUntilDone();
  front_wings.set_value(true);
  chassis.moveToPoint(-5.81, -12, 2000);
  chassis.waitUntilDone();
  front_wings.set_value(false);
  chassis.moveToPoint(-31, -63, 5000, false, 80);
  }

void skills(){

}

void trustAlliance() {}

void ace() {
  chassis.setPose(-47.6, -56.6, 45);
  hang_piston.set_value(true);
  chassis.turnTo(-10.9, -10, 1000);
  chassis.waitUntilDone();
  front_wings.set_value(true);
  intake = -120;
  chassis.moveToPoint(-10.9, -10, 2000);
  chassis.waitUntil(20);
  front_wings.set_value(false);
  chassis.waitUntilDone();
  chassis.moveToPoint(-44, -53, 2000, false);
  chassis.waitUntilDone();
  back_wings.set_value(true);
  chassis.turnTo(-80, -80, 2000, false);
  chassis.waitUntilDone();
  back_wings.set_value(false);
  chassis.turnTo(-4, -59, 2000);
  chassis.waitUntilDone();
  intake = 120;
  chassis.moveToPoint(-8, -59, 2000);



