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
  
  hang_piston.set_value(true);
  chassis.setPose(-47, -54, 0);
  chassis.turnTo(47, 1, 2000);
  back_wings.set_value(true);
  cata.state = 3;
  //pros::delay(30000);
  cata.state = 0;
  back_wings.set_value(false);
  chassis.turnTo(-4, -59, 2000, false);
  chassis.moveToPoint(-4.805, -59.328, 2000, false);
  chassis.turnTo(42, -56, 2000, false);
  chassis.moveToPoint(42.122, -56.997, 2000, false);
  chassis.turnTo(59.4, -45.081, 2000, false);
  chassis.moveToPoint(59.4, -45.081, 2000, false);
  chassis.turnTo(59.599, -30.582, 2000, false);
  chassis.moveToPoint(59.599, -30.582, 2000, false);
  chassis.moveToPoint(59.599, -45.478, 2000);
  chassis.turnTo(10.328, -29.714, 2000);
  chassis.moveToPoint(10.328, -29.714, 2000);
  chassis.turnTo(10.725, -17.599, 2000);
  chassis.moveToPoint(10.725, -17.599, 2000);
  chassis.turnTo(39.126, -15.017, 2000, false);
  chassis.moveToPoint(39.126, -15.017, 2000, false);
  chassis.turnTo(8.541, -2.307, 2000);
  chassis.moveToPoint(8.541, -2.307, 2000);
  chassis.moveToPoint(38.531, -1.115, 2000, false);
  chassis.turnTo(7.746, 13.185, 2000);
  chassis.moveToPoint(7.746, 13.185, 2000);
  chassis.moveToPoint(38.729, 12.39, 2000, false);
  chassis.turnTo(8.739, 5.638, 2000);
  chassis.moveToPoint(8.739, 5.638, 2000);
  back_wings.set_value(true);
  chassis.moveToPoint(43.098, 6.432, 2000, false);
  chassis.turnTo(4.171, -26.537, 2000);
  chassis.moveToPoint(4.171, -26.537, 2000);
  chassis.moveToPoint(44.489, -10.648, 2000, false);
  chassis.moveToPoint(4.171, -26.537, 2000);
}

void trustAlliance() {
  /*
  chassis.setPose(0, 0, 0);
  chassis.moveToPoint(0, 24, 5000);
  chassis.waitUntilDone();
  chassis.moveToPoint(0, 0, 5000, false);
  chassis.waitUntilDone();


  chassis.turnTo(45, 45, 5000);
  chassis.turnTo(-45, -45, 5000);
  chassis.turnTo(0, 10, 5000);
  chassis.turnTo(45, 45, 5000);
  chassis.turnTo(-45, -45, 5000);
  chassis.turnTo(0, 10, 5000);
  */
}

void ace() {
  chassis.setPose(-47.6, -56.6, 45);
  hang_piston.set_value(true);
  //chassis.turnTo(-10.9, -10, 2000);
  //chassis.waitUntilDone();
  front_wings.set_value(true);
  intake = -120;
  //chassis.moveToPoint(-10.9, -10, 2000);
  chassis.moveToPose(-10.9, -10, 45, 2000);
  chassis.waitUntil(20);
  front_wings.set_value(false);
  chassis.waitUntilDone();
  chassis.turnTo(-43,-54,2000, false);
  chassis.moveToPoint(-43, -54, 2000, false);
  chassis.waitUntilDone();
  back_wings.set_value(true);
  chassis.turnTo(-102, -98, 2000, true);
  chassis.waitUntilDone();
  back_wings.set_value(false);
  chassis.turnTo(-29, -60, 2000);
  chassis.moveToPoint(-29, -60, 2000);
  chassis.waitUntilDone();
  intake = 120;
  chassis.turnTo(-8, -62, 2000);
  chassis.moveToPoint(-8, -62, 2000);
}



