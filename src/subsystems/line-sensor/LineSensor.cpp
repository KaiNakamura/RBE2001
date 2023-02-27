#include "LineSensor.h"

LineSensor::LineSensor() {
}

void LineSensor::setup() {
  pinMode(LEFT_0_PIN, INPUT);
  pinMode(LEFT_1_PIN, INPUT);
  pinMode(RIGHT_0_PIN, INPUT);
  pinMode(RIGHT_1_PIN, INPUT);
  reset();
}

void LineSensor::update() {
  left0Raw += analogRead(LEFT_0_PIN);
  left1Raw += analogRead(LEFT_1_PIN);
  right0Raw += analogRead(RIGHT_0_PIN);
  right1Raw += analogRead(RIGHT_1_PIN);

  long elapsed = millis() - lastTime;
  if (elapsed > READ_TIME) {
    leftValue = lerp((left1Raw - left0Raw) / READ_TIME, LEFT_WHITE, LEFT_BLACK);
    rightValue = lerp((right1Raw - right0Raw) / READ_TIME, RIGHT_WHITE, RIGHT_BLACK);
    reset();
  }
}

void LineSensor::reset() {
  lastTime = millis();
  left0Raw = 0;
  left1Raw = 0;
  right0Raw = 0;
  right1Raw = 0;
}

double LineSensor::lerp(double value, double min, double max) {
  return (value - min) / (max - min);
}

double LineSensor::getValue() {
  return leftValue - rightValue;
}
