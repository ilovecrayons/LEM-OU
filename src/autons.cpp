#include "main.h"
#include "config.hpp"



ASSET(closesafe1_txt)
ASSET(closesafe2_txt)
void close() {
//TODO: modify wait time
  chassis.setPose(-47, -58, 180);
  intake = -60;
  pros::delay(500);
  intake = 0;
  chassis.follow(closesafe1_txt, 15, 2000, false);
  chassis.waitUntilDone();
  chassis.follow(closesafe2_txt, 15, 10000);
  chassis.waitUntil(15);
  intake = -60;
  left_wing.set_value(true);
  chassis.waitUntil(30);
  left_wing.set_value(false);
  
}

void sixRush() {}

void sixSafe(){}

void skills(){

}

void trustAlliance(){

}


