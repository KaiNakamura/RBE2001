#include <Arduino.h>
#include <Romi32U4.h>
#include "BlueMotor.h"

long count = 0;

static int encAVal;
static int encBVal;

BlueMotor::BlueMotor() {
}

void BlueMotor::setup() {
  pinMode(PWM_OUT_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(ENCA_PIN, INPUT);
  pinMode(ENCB_PIN, INPUT);
  TCCR1A = 0xA8; // 0b10101000, gcl: added OCR1C for adding a third PWM on pin 11
  TCCR1B = 0x11; // 0b00010001
  ICR1 = 400;
  OCR1C = 0;

  attachInterrupt(digitalPinToInterrupt(ENCA_PIN), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCB_PIN), isrB, CHANGE);
  reset();
}

void BlueMotor::update() {
  if (isAtTarget()) {
    setEffort(0);
  } else {
    double error = target - getPosition(units);
    setEffort(MOVE_TO_K_P * error);
  }
}

void BlueMotor::reset() {
  noInterrupts();
  count = 0;
  interrupts();

  target = getPosition(ROTATIONS);
  units = ROTATIONS;
}

void BlueMotor::isrA() {
  encAVal = digitalRead(ENCA_PIN);
  if (encAVal == encBVal) {
    count--;
  } else {
    count++;
  }
}

void BlueMotor::isrB() {
  encBVal = digitalRead(ENCB_PIN);
  if (encAVal == encBVal) {
    count++;
  } else {
    count--;
  }
}

double BlueMotor::toTicks(double position, Units units) {
  switch (units) {
    case TICKS:
      return position;
    case ROTATIONS:
      return position * ENCODER_RESOLUTION;
    case DEGREES:
      return (position / 360) * ENCODER_RESOLUTION;
  }

  Serial.println("Could not convert to ticks with given units: " + units);
  return 0;
}

double BlueMotor::getTicks() {
  long tempCount = 0;
  noInterrupts();
  tempCount = count;
  interrupts();
  return tempCount;
}

double BlueMotor::getRotations() {
  return getTicks() / ENCODER_RESOLUTION;
}

double BlueMotor::getDegrees() {
  return getRotations() * 360;
}

double BlueMotor::getPosition(Units units) {
  switch (units) {
    case TICKS:
      return getTicks();
    case ROTATIONS:
      return getRotations();
    case DEGREES:
      return getDegrees();
  }

  Serial.println("Could not get position with units: " + units);
  return 0;
}

/**
 * @param effort A number from -1 to 1
 */
void BlueMotor::setEffort(double effort) {
  setEffort(abs(effort), effort < 0);
}

/**
 * @param effort A number from 0 to 1
 * @param clockwise Whether to spin clockwise or not
 */
void BlueMotor::setEffort(double effort, bool clockwise) {
  if (clockwise) {
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
  } else {
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
  }
  
  OCR1C = 400 * constrain(effort, 0, 1);
}

bool BlueMotor::isAtTarget() {
  double error = target - getPosition(units);
  return toTicks(abs(error), units) < IS_AT_TARGET_TOLERANCE;
}

/**
 * Move to encoder position within the specified tolerance
 * in the header file using proportional control then stop
 */
void BlueMotor::moveTo(double target, Units units) {
  this->target = target;
  this->units = units;
}

void BlueMotor::moveToByTicks(double ticks) {
  moveTo(ticks, TICKS);
}

void BlueMotor::moveToByRotations(double rotations) {
  moveTo(rotations, ROTATIONS);
}

void BlueMotor::moveToByDegrees(double degrees) {
  moveTo(degrees, DEGREES);
}

void BlueMotor::moveToStartingSetpoint() {
  moveTo(STARTING_SETPOINT, ROTATIONS);
}

void BlueMotor::moveToRoof45DegreeSetpoint() {
  moveTo(ROOF_45_DEGREE_SETPOINT, ROTATIONS);
}

void BlueMotor::moveToRoof25DegreeSetpoint() {
  moveTo(ROOF_25_DEGREE_SETPOINT, ROTATIONS);
}
