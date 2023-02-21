#include "Ultrasonic.h"
#include <Arduino.h>
#include <Romi32U4.h>
#include "Constants.h"

Ultrasonic::Ultrasonic() {
}

void Ultrasonic::setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  reset();
}

// TODO: Rewrite so that this doesn't use delay
void Ultrasonic::update() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  distance = pulseIn(ECHO_PIN, HIGH) * DURATION_TO_CENTIMETERS;
}

void Ultrasonic::reset() {
  distance = 0;
}

double Ultrasonic::getDistance(){
  return distance;
}
