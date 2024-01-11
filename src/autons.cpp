#include "main.h"
#include "config.hpp"



ASSET(closesafe1_txt)
ASSET(closedisrupt_txt)
void closeSafe() {

  chassis.setPose(-47.8, -53.9, 0);
  left_wing.set_value(true);
  intake = -60;
  pros::delay(500);
  chassis.turnTo(-100, -100, 10000);
  chassis.waitUntilDone(); 
  left_wing.set_value(false);
  chassis.turnTo(100, -53, 10000);
  intake = 127;
  chassis.follow(closesafe1_txt, 15, 5000, true);
  
  
}

void closeDisrupt() {
  intake = -30;
  chassis.setPose(-47.8, -53.9, 0);
  chassis.moveToPoint(-13.875, -6.346, 5000);
  chassis.waitUntil(30);
  left_wing.set_value(true);
  chassis.waitUntilDone();
  chassis.turnTo(46, 8, 2000);
  chassis.waitUntilDone();
  chassis.turnTo(-46, 8, 2000);
  chassis.waitUntilDone();
  left_wing.set_value(false);
  intake = 120;
  pros::delay(500);
  chassis.turnTo(-13, -100, 2000);
  chassis.waitUntilDone();
  chassis.follow(closedisrupt_txt, 15, 5000, true);
  chassis.waitUntil(30);
  left_wing.set_value(true);
  chassis.waitUntil(70);
  left_wing.set_value(false);


}

void skills(){

}

void trustAlliance(){

}


