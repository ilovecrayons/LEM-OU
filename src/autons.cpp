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

  chassis.setPose(-35, -56.4, 0);
  intake = -15;
  pros::delay(500);
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
  chassis.follow(closedisrupt_txt, 15, 10000, true);
  chassis.waitUntil(30);
  left_wing.set_value(true);
  chassis.waitUntil(70);
  left_wing.set_value(false);


}

void skills(){

}

void trustAlliance(){

}


