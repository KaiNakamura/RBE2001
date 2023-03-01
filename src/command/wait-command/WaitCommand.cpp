#include <Arduino.h>
#include "WaitCommand.h"

WaitCommand::WaitCommand(unsigned long millis) {
  duration = millis;
}

WaitCommand::WaitCommand(int millis) {
  duration = millis;
}

void WaitCommand::execute() {
  if (start == 0) {
    start = millis();
  }
}

bool WaitCommand::isFinished() {
  return start && (millis() > start + duration);
}

void WaitCommand::end() {
  Serial.print("Waited for ");
  Serial.println(duration);
}