#include "Ultrasonic.h"
#include <Arduino.h>
#include <Romi32U4.h>
#include <HCSR04.h>
#include "Constants.h"

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
