#include "Robot.h"

Robot *Robot::instance = 0;

Robot::Robot() {
}

Robot *Robot::getInstance() {
  if (!instance) {
    instance = new Robot();
  }
  return instance;
}

void Robot::setup() {
  // subsystems.push_back(&battery);
  subsystems.push_back(&drivebase);
  subsystems.push_back(&blueMotor);
  // subsystems.push_back(&clawGripper);
  subsystems.push_back(&linearGripper);
  subsystems.push_back(&ultrasonic);
  subsystems.push_back(&lineSensor);
  subsystems.push_back(&irSensor);

  for (size_t i = 0; i < subsystems.size(); i++) {
    subsystems.at(i)->setup();
  }
}

void Robot::update() {
  for (size_t i = 0; i < subsystems.size(); i++) {
    subsystems.at(i)->update();
  }
}

void Robot::reset() {
  for (size_t i = 0; i < subsystems.size(); i++) {
    subsystems.at(i)->reset();
  }
}

void Robot::stop() {
  drivebase.stop();
  blueMotor.setEffort(0);
  linearGripper.stop();
}

// Battery *Robot::getBattery() {
//   return &battery;
// }

Drivebase *Robot::getDrivebase() {
  return &drivebase;
}

BlueMotor *Robot::getBlueMotor() {
  return &blueMotor;
}

LinearGripper *Robot::getLinearGripper() {
  return &linearGripper;
}

Ultrasonic *Robot::getUltrasonic() {
  return &ultrasonic;
}

LineSensor *Robot::getLineSensor() {
  return &lineSensor;
}

IRSensor *Robot::getIRSensor() {
  return &irSensor;
}
