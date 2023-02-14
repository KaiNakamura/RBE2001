#include "BlueMotor.h"
#include <Arduino.h>
#include <Romi32U4.h>
#include "Constants.h"

long oldValue = 0;
long newValue;
long count = 0;
unsigned time = 0;

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

void BlueMotor::reset() {
  noInterrupts();
  count = 0;
  interrupts();
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

/**
 * Move to encoder position within the specified tolerance
 * in the header file using proportional control then stop
 */
bool BlueMotor::moveTo(double target, Units units) {
  double error = target - getPosition(units);
  if (toTicks(abs(error), units) < MOVE_TO_TOLERANCE) {
    setEffort(0);
    return true;
  } else {
    setEffort(MOVE_TO_K_P * error);
    return false;
  }
}

bool BlueMotor::moveToByTicks(double ticks) {
  return moveTo(ticks, TICKS);
}

bool BlueMotor::moveToByRotations(double rotations) {
  return moveTo(rotations, ROTATIONS);
}

bool BlueMotor::moveToByDegrees(double degrees) {
  return moveTo(degrees, DEGREES);
}

void BlueMotor::moveToSetpoint(double setpoint, Units units) {
  while (!moveTo(setpoint, units));
}

void BlueMotor::moveToStartingSetpoint() {
  moveToSetpoint(STARTING_SETPOINT, ROTATIONS);
}

void BlueMotor::moveToRoof45DegreeSetpoint() {
  moveToSetpoint(ROOF_45_DEGREE_SETPOINT, ROTATIONS);
}

void BlueMotor::moveToRoof25DegreeSetpoint() {
  moveToSetpoint(ROOF_25_DEGREE_SETPOINT, ROTATIONS);
}
