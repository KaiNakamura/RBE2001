#include "ClawGripper.h"
#include <Arduino.h>
#include <Romi32U4.h>
#include "Constants.h"
#include <Servo32u4.h>

Servo32U4Pin5 servo;

ClawGripper::ClawGripper() {
}

void ClawGripper::setup() {
  servo.attach();
  pinMode(ENCODER_PIN, INPUT);
}

void ClawGripper::update() {

}

void ClawGripper::reset() {
}

void ClawGripper::open() {
  servo.writeMicroseconds(OPEN_SETPOINT);
}

void ClawGripper::close() {
  servo.writeMicroseconds(CLOSE_SETPOINT);
}

double ClawGripper::getPosition() {
  return analogRead(ENCODER_PIN);
}
