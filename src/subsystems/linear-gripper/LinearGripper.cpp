#include "LinearGripper.h"
#include <Arduino.h>
#include <Romi32U4.h>
#include "Constants.h"
#include <Servo32u4.h>

Servo32U4Pin6 linearServo;

LinearGripper::LinearGripper() {
}

void LinearGripper::setup() {
  linearServo.attach();
  pinMode(POTENTIOMETER_PIN, INPUT);
}

void LinearGripper::update() {
}

void LinearGripper::reset() {
}

double LinearGripper::getPosition() {
  int adc = analogRead(POTENTIOMETER_PIN);
  return adc;
}

void LinearGripper::open() {
  double startTime = millis();
  while (getPosition() < OPEN_SETPOINT) {
    Serial.print("Position: ");
    Serial.println(getPosition());
    linearServo.writeMicroseconds(SERVO_DOWN);
  }
  linearServo.writeMicroseconds(SERVO_STOP);
}

void LinearGripper::close() {
  double startTime = millis();
  while (getPosition() > CLOSED_SETPOINT) {
    Serial.print("Position: ");
    Serial.println(getPosition());
    linearServo.writeMicroseconds(SERVO_UP);
  }
  linearServo.writeMicroseconds(SERVO_STOP);
}

void LinearGripper::setEffort(double effort) {

}

bool LinearGripper::moveTo(double target) {
  double error = target - getPosition();
  if (error < MOVE_TO_TOLERANCE) {
    setEffort(0);
    return true;
  } else {
    setEffort(MOVE_TO_K_P * error);
    return false;
  }
}