#include "JobScheduler.hpp"

// Temporary declarations
class FlapDiverterValve {
 public:
  void actuateState(int desiredStateValue);
};

/**
 * @brief Defines a job that incrementally moves a FlapDiverterValve until it
 * reaches its desired state.
 *
 */
class FlapDiverterValveJob : public Job {
 private:
  // Temporary value used to determine how many times the valve will move
  // until it reaches desired state.
  // TODO improve the metric for deciding step sizes.
  static const int NUM_STEPS = 3;
  FlapDiverterValve* valve;
  int endState;
  int currState;
  int stepSize;

 int remainingDistance(void) {
	return endState - currState;
 }

 public:
  FlapDiverterValveJob(FlapDiverterValve* flapDiverterValve, int desiredState)
      : valve(flapDiverterValve), endState(desiredState) {
		// set currState to the current state of the valve
		stepSize = (endState - currState) / NUM_STEPS;
	  }

  bool isComplete(void) override {
	return currState == endState;
  }

  void execute(void) override {
	if(!isComplete()) {
		// CASE: negative step size and next step is within bounds
		if(stepSize < 0 && remainingDistance() >= stepSize) {
			valve->actuateState(currState + stepSize);
			currState += stepSize;
		} 
		// CASE: positive step size and next step is within bounds
		else if(stepSize > 0 && remainingDistance() <= stepSize) {
			valve->actuateState(currState + stepSize);
			currState += stepSize;
		}
		// CASE: next step will result in completion
		else {
			valve->actuateState(endState);
			currState = endState;
		}
	}
  }
};