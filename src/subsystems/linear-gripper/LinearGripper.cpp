#include "LinearGripper.h"

LinearGripper::LinearGripper() {
}

void LinearGripper::setup() {
  servo.attach();
  pinMode(POTENTIOMETER_PIN, INPUT);
  reset();
}

void LinearGripper::update() {
  switch (state) {
    case OPENING:
      if (isOpen()) {
        state = OPEN;
      } else if (isStuck()) {
        close();
      } else {
        servo.writeMicroseconds(SERVO_OPEN);
      }
      break;
    case CLOSING:
      if (isClosed()) {
        state = CLOSED;
      } else if (isStuck()) {
        open();
      } else {
        servo.writeMicroseconds(SERVO_CLOSE);
      }
      break;
    default:
      servo.writeMicroseconds(SERVO_STOP);
      break;
  }

  // Serial.print("Position: ");
  // Serial.print(getPosition());
  // Serial.print(", State: ");
  // Serial.println(state);
}

void LinearGripper::reset() {
  state = CLOSED;
  resetStuckCalculations();
}

void LinearGripper::resetStuckCalculations(long delay) {
  lastTime = millis() + delay;
  lastPosition = getPosition();
  numFailedMovements = 0;
}

void LinearGripper::resetStuckCalculations() {
  resetStuckCalculations(0);
}

void LinearGripper::open() {
  if (state != OPEN) {
    state = OPENING;
    resetStuckCalculations(SERVO_ACCELERATION_TIME);
  }
}

void LinearGripper::close() {
  if (state != CLOSED) {
    state = CLOSING;
    resetStuckCalculations(SERVO_ACCELERATION_TIME);
  }
}

int LinearGripper::getPosition() {
  return analogRead(POTENTIOMETER_PIN);
}

bool LinearGripper::isAtPosition(int position) {
  int error = position - getPosition();
  return abs(error) <= IS_AT_POSITION_TOLERANCE;
}

bool LinearGripper::isOpen() {
  return isAtPosition(OPEN_POSITION);
}

bool LinearGripper::isClosed() {
  return isAtPosition(CLOSED_POSITION);
}

bool LinearGripper::isStuck() {
  long elapsed = millis() - lastTime;
  if (elapsed > DISTANCE_COVERED_TIME_FRAME) {
    // Check the distance covered in the given time frame
    int distanceCovered = abs(getPosition() - lastPosition);
    // If gripper hasn't covered enough distance, count as a fail
    if (distanceCovered < MIN_DISTANCE_COVERED_BEFORE_STUCK) {
      numFailedMovements++;
    }
    // Else, reset for next time frame
    else {
      resetStuckCalculations();
    }
  }

  // If gripper failed to move too many times, it's stuck
  return numFailedMovements > MAX_NUM_FAILED_MOVEMENTS;
}