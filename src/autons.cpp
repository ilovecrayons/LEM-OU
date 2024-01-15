#include "main.h"
#include "config.hpp"
#include "pros/rtos.hpp"



ASSET(closesafe1_txt)
ASSET(closedisrupt_txt)
void closeSafe() {

  chassis.setPose(-35.5, -55, 0);
  intake = -100;
  pros::delay(500);
  chassis.follow(closesafe1_txt, 6, 10000);
  chassis.waitUntil(27);
  left_wing.set_value(true);
  chassis.waitUntil(65);
  intake = 120;
  left_wing.set_value(false);

}

void closeDisrupt() {

  chassis.setPose(-35, -56.4, 0);
  intake = -60;
  
  chassis.turnTo(-33.688, -11.095, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-33.688, -11.095, 3000);
  chassis.waitUntil(35);
  intake = 120;
  chassis.turnTo(-9.803, -11.095, 2000);
  chassis.waitUntilDone();
  left_wing.set_value(true);
  chassis.moveToPoint(-7.803, -11.095, 2000);
  chassis.waitUntilDone();
  left_wing.set_value(false);
  chassis.moveToPoint(-14, -10, 1000, false);
  chassis.waitUntilDone();
  /*
  chassis.turnTo(-46, 20, 2000);
  chassis.waitUntilDone();

  pros::delay(500);
  */
  chassis.turnTo(-13, -100, 2000);
  chassis.waitUntilDone();
  chassis.follow(closedisrupt_txt, 10, 10000, true);
  chassis.waitUntil(30);
  left_wing.set_value(true);
  chassis.waitUntil(70);
  left_wing.set_value(false);


}

void skills(){

}

void trustAlliance(){

}


