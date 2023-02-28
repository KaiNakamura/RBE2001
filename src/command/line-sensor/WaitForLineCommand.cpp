#include "subsystems/robot/Robot.h"
#include "WaitForLineCommand.h"

WaitForLineCommand::WaitForLineCommand() {
  lineSensor = Robot::getInstance()->getLineSensor();
}

void WaitForLineCommand::execute() {
}

bool WaitForLineCommand::isFinished() {
  return (
    lineSensor->getLeftValue() > IS_ON_LINE_THRESHOLD &&
    lineSensor->getRightValue() > IS_ON_LINE_THRESHOLD
  );
}

void WaitForLineCommand::end() {
}