#include "LineSensor.h"

LineSensor::LineSensor() {
}

void LineSensor::setup() {
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(EMITTER_PIN, OUTPUT);
  reset();
}

void LineSensor::update() {
  digitalWrite(EMITTER_PIN, HIGH);

  leftRaw += analogRead(LEFT_PIN);
  rightRaw += analogRead(RIGHT_PIN);

  long elapsed = millis() - lastTime;
  if (elapsed > READ_TIME) {
    leftValue = leftRaw / READ_TIME;
    rightValue = rightRaw / READ_TIME;

    Serial.print(leftValue);
    Serial.print("\t");
    Serial.print(rightValue);
    Serial.print("\t");
    Serial.println(getValue());

    reset();
  }
}

void LineSensor::reset() {
  lastTime = millis();
  leftRaw = 0;
  rightRaw = 0;
}

double LineSensor::getValue() {
  return leftValue - rightValue;
}
