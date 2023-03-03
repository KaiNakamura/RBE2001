#include "Ultrasonic.h"
#include <HCSR04.h>

Ultrasonic::Ultrasonic() {
}

void Ultrasonic::setup() {
  HCSR04.begin(TRIG_PIN, ECHO_PIN);
}

void Ultrasonic::update() {
}

void Ultrasonic::reset() {
}

double Ultrasonic::getDistance(){
  return HCSR04.measureDistanceCm()[0];
}
