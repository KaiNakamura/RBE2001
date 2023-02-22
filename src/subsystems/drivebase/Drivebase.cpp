#include "Drivebase.h"

// TODO: Protect chassis somehow, but code won't compile if it's private :(
Chassis chassis;

Drivebase::Drivebase() {

}

void Drivebase::setup() {
  chassis.init();
}

void Drivebase::update() {
}

void Drivebase::reset() {
}

void Drivebase::setMotors(double left, double right) {
  chassis.setMotorEfforts(420 * left, 420 * right);
}

void Drivebase::stop() {
  chassis.idle();
}