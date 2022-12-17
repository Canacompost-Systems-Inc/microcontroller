#include "JobScheduler.hpp"


// Temporary declarations
class RotaryValve {
 public:
  void step(void);
  void resetPosition(void);
};

class RotaryValveJob : public Job {
 private:
  RotaryValve* valve;
  int endState;
  int currState;

 public:
  RotaryValveJob(RotaryValve* rotaryValve, int desiredState)
      : valve(rotaryValve), endState(desiredState) {
    valve->resetPosition();
  }

  bool isComplete(void) override { return currState == endState; }

  void execute(void) override {
    if (!isComplete()) {
      valve->step();
      currState++;
    }
  }
};