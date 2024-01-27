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

void trustAlliance(){

}


