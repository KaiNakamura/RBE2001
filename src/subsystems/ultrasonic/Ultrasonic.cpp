#include "Ultrasonic.h"
#include <Arduino.h>
#include <Romi32U4.h>
#include "Constants.h"

static int duration;
static float distance;

Ultrasonic::Ultrasonic() {
}

void Ultrasonic::setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  reset();
}

void Ultrasonic::update() {

}

void Ultrasonic::reset() {
  noInterrupts();

  interrupts();
}

float Ultrasonic::findDistance(){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}
