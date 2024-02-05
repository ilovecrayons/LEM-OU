#include "config.hpp"
#include "main.h"
#include "pros/rtos.hpp"


constexpr int EARLY_EXIT{0};
constexpr int MIN_SPEED{0};

ASSET(closesafe1_txt)
ASSET(closedisrupt_txt)
void closeSafe() {
  chassis.setPose(-46.451, -57.626, 135);
  hang_piston.set_value(true);
  pros::delay(2000);
  hang_piston.set_value(false);
  back_wings.set_value(true);
  pros::delay(500);
  intake = 120;
  chassis.turnTo(-55, -9, 1000);
  chassis.waitUntil(45);
  back_wings.set_value(false);
  chassis.turnTo(-30, -61, 1000);
  chassis.waitUntilDone();
  chassis.moveToPoint(-30, -61, 3000, true);
  chassis.turnTo(-8, -61, 1000);
  chassis.waitUntilDone();
  pros::delay(6000);
  chassis.moveToPoint(-10.7, -61, 3000, true);
}

void closeDisrupt() {
  chassis.setPose(-35, -55.4, 0);
  hang_piston.set_value(true);
  // chassis.turnTo(-24.994, -11, 1000);
  intake = -120;
  front_wings.set_value(true);
  chassis.moveToPoint(-24.994, -11.075, 2000);
  chassis.waitUntil(45);
  hang_piston.set_value(false);
  front_wings.set_value(false);
  chassis.moveToPoint(-27, -13.5, 2000, false);
  chassis.waitUntilDone();
  chassis.turnTo(-5.8, -12, 2000);
  chassis.waitUntilDone();
  front_wings.set_value(true);
  chassis.moveToPoint(-3, -12, 2000);
  chassis.waitUntilDone();
  front_wings.set_value(false);
  chassis.turnTo(-54, -56, 2000, false);
  chassis.moveToPoint(-48, -51, 2000, false, 80);
  chassis.waitUntilDone();
  chassis.turnTo(20, -80, 2000);
  chassis.waitUntilDone();

  intake = 120;
}

void skills() {

  hang_piston.set_value(true);
  chassis.setPose(-38, -58, 90);
  chassis.turnTo(-56, -41, 2000, false);
  chassis.moveToPoint(-56, -41, 2000, false);
  chassis.turnTo(46, -3, 2000);
  hang_piston.set_value(false);
  chassis.waitUntilDone();
  back_wings.set_value(true);
  cata.state = 3;
  pros::delay(24000);
  cata.state = 0;
  back_wings.set_value(false);
  chassis.turnTo(-58, -30, 2000, false);
  chassis.moveToPoint(-56, -26, 2000, false);
  chassis.moveToPoint(-56, -41, 2000);
  chassis.turnTo(-38, -59.5, 2000, false);
  chassis.moveToPoint(-38, -59.5, 2000, false);
  chassis.turnTo(39, -59.5, 2000, false);
  chassis.moveToPoint(39, -59.5, 2000, false);
  chassis.turnTo(63, -43, 2000, false);
  chassis.moveToPoint(63, -43, 2000, false);
  chassis.turnTo(63, -29, 2000, false);
  chassis.moveToPoint(63, -28.582, 2000, false);
  chassis.moveToPoint(63, -45.478, 2000);
  chassis.turnTo(15.328, -29.714, 2000);
  chassis.moveToPoint(15.328, -29.714, 2000);
  chassis.turnTo(15.725, -22, 2000);
  chassis.moveToPoint(15.725, -22, 2000);
  chassis.turnTo(39.126, -22, 2000, false);
  chassis.moveToPoint(39.126, -22, 2000, false);
  chassis.moveToPoint(13.725, -22, 2000);
 
  chassis.turnTo(13, 0, 2000);
  chassis.moveToPoint(13, 0, 2000);
  chassis.turnTo(39, 0, 2000, false);
  back_wings.set_value(true);
  chassis.moveToPoint(39, 0, 2000, false);
  chassis.moveToPoint(11, 0, 2000);
  chassis.waitUntil(5);
  back_wings.set_value(false);
  chassis.turnTo(11, 25, 2000);
  chassis.moveToPoint(11, 25, 2000);
  chassis.turnTo(40, 5, 2000, false);
  chassis.moveToPoint(50, 5, 2000, false);
  back_wings.set_value(true);
  chassis.moveToPoint(13, 25, 2000);
  chassis.waitUntil(5);
  back_wings.set_value(false);

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
  chassis.setPose(-47.6, -56.6, 38);
  hang_piston.set_value(true);
  // chassis.turnTo(-10.9, -10, 2000);
  // chassis.waitUntilDone();
  front_wings.set_value(true);
  intake = -120;
  chassis.moveToPoint(-10.9, -10, 2000);
  chassis.waitUntil(20);
  front_wings.set_value(false);
  chassis.waitUntilDone();
  chassis.moveToPoint(-45, -55, 2000, false);
  chassis.waitUntilDone();
  back_wings.set_value(true);
  chassis.turnTo(-93, -76, 2000, true, 80);
  chassis.waitUntilDone();
  back_wings.set_value(false);
  intake = 120;
  chassis.turnTo(-29, -65, 2000);
  chassis.moveToPoint(-29, -60, 2000);

  chassis.moveToPoint(-8, -70, 2000);
}

void farRush() {
  chassis.setPose(35.6, -55.8, 0);
  hang_piston.set_value(true);
  chassis.moveToPoint(29.462, -19.234, 2000);
  chassis.turnTo(11, -6, 2000);
  intake = -120;
  chassis.moveToPoint(11.044, -6.501, 2000);
  hang_piston.set_value(false);
  chassis.turnTo(40, -6, 2000, true);
  front_wings.set_value(true);
  chassis.moveToPoint(40.149, -6.273, 2000, true);
  intake = 120;
  chassis.turnTo(11, -20, 2000);
  front_wings.set_value(false);
  chassis.moveToPoint(11.271, -20.826, 2000);
  intake = -120;
  chassis.turnTo(46, -54, 2000);
  chassis.moveToPoint(46.743, -54.251, 2000);
  chassis.turnTo(57, -45, 2000, false);
  chassis.moveToPoint(57.885, -45.838, 2000, false);
  back_wings.set_value(true);
  chassis.turnTo(58, -29, 2000, false);
  chassis.moveToPoint(58.794, -29.466, 2000, false);
  pros::delay(500);
  back_wings.set_value(false);
}

void driverStart() {
  //hang_piston.set_value(true);
  chassis.setPose(-38, -58, 90);
  chassis.turnTo(-56, -41, 2000, false);
  chassis.moveToPoint(-56, -41, 2000, false);
  chassis.turnTo(46, -3, 2000);
  //hang_piston.set_value(false);
  chassis.waitUntilDone();
  back_wings.set_value(true);
  cata.state = 3;
  
}
