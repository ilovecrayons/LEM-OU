#include "main.h"
#include "config.hpp"



ASSET(closesafe1_txt)
ASSET(closesafe2_txt)
void close() {
  left_wing.set_value(true);
  intake = -60;
  pros::delay(500);
  chassis.turnTo(-100, -58, 1000);
  chassis.waitUntilDone();
  left_wing.set_value(false);
  chassis.follow(closesafe1_txt, 15, 2000);
  pros::delay(1000);
  intake = 120;
  
  chassis.waitUntilDone();
  chassis.turnTo(-47, -58, 1000);
  chassis.waitUntilDone();
  chassis.setPose(-58, -31, 155);
  chassis.follow(closesafe2_txt, 15, 10000);
  chassis.waitUntilDone();
  intake = 0;

}

void sixRush() {}

void sixSafe(){}

void skills(){

}

void trustAlliance(){

}


