#pragma once

class Subsystem {
public:
  virtual void setup() = 0;
  virtual void update() = 0;
  virtual void reset() = 0;

private:
};