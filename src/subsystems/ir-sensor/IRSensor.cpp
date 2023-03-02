#include "IRSensor.h"

// TODO: Protect decoder somehow, but code won't compile if it's private :(
IRDecoder decoder(14);

IRSensor::IRSensor() {
}

void IRSensor::setup() {
  decoder.init();
}

void IRSensor::update() {
}

void IRSensor::reset() {
}

int16_t IRSensor::getCode() {
  return decoder.getKeyCode();
}
