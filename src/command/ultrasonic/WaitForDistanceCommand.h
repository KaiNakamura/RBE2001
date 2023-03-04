#pragma once

#include "subsystems/ultrasonic/Ultrasonic.h"
#include "command/Command.h"

class WaitForDistanceCommand: public Command {
  public:
    WaitForDistanceCommand(double distance);
    void execute();
    bool isFinished();
    void end();
  private:
    Ultrasonic *ultrasonic;
    static const int MIN_NUM_READINGS = 10;
    double distance, numReadings;
};
