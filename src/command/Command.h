#pragma once

class Command {
public:
  virtual void execute() = 0;
  virtual bool isFinished() = 0;
  virtual void end() = 0;

private:
};