#pragma once

#include "Constants.h"

class Subsystem {
public:
  virtual void setup();
  virtual void update();
  virtual void reset();

private:
};