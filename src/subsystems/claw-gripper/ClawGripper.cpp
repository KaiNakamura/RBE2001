#include "ClawGripper.h"

ClawGripper::ClawGripper() {
}

void ClawGripper::setup() {
  servo.attach();
  pinMode(ENCODER_PIN, INPUT);
  reset();
}

void ClawGripper::update() {
  switch (state) {
    case OPENING:
      servo.writeMicroseconds(OPEN_SETPOINT);
      if (isOpen()) {
        state = OPEN;
      } else if (isStuck()) {
        close();
      }
      break;
    case CLOSING:
      servo.writeMicroseconds(CLOSED_POSITION);
      if (isClosed()) {
        state = CLOSED;
      } else if (isStuck()) {
        open();
      }
      break;
    default:
      break;
  }

  Serial.print("Claw Gripper State: ");
  Serial.println(state);
}

void ClawGripper::reset() {
  state = CLOSED;
  lastTimeBeforeMoving = 0;
}

void ClawGripper::open() {
  if (state != OPEN) {
    state = OPENING;
    lastTimeBeforeMoving = millis();
  }
}

void ClawGripper::close() {
  if (state != CLOSED) {
    state = CLOSING;
    lastTimeBeforeMoving = millis();
  }
}

int ClawGripper::getPosition() {
  return analogRead(ENCODER_PIN);
}

bool ClawGripper::isAtPosition(int position) {
  int error = position - getPosition();
  return abs(error) <= IS_AT_POSITION_TOLERANCE;
}

bool ClawGripper::isOpen() {
  return isAtPosition(OPEN_POSITION);
}

bool ClawGripper::isClosed() {
  return isAtPosition(CLOSED_POSITION);
}

bool ClawGripper::isStuck() {
  double timeSpentMoving = millis() - lastTimeBeforeMoving;
  return timeSpentMoving > MAX_STUCK_TIME;
}