#include <iostream>

#include "JobScheduler.hpp"

class JobA : public Job {
 public:
  int test;

  JobA(void) : test(0) {}
  ~JobA(void) = default;

  bool isComplete(void) override { return test == 10; }

  void execute(void) override {
    if (!isComplete()) {
      std::cout << "JobA " << test << '\n';
      test += 1;
      if (isComplete()) {
        std::cout << "JobA complete\n";
      }
    }
  }
};

class JobB : public Job {
 public:
  int val;
  int desired;

  JobB(int d) : val(0), desired(d) {}

  bool isComplete(void) override { return val == desired; }

  void execute(void) override {
    if (!isComplete()) {
      std::cout << "JobB " << val << '\n';
      val++;
      if (isComplete()) {
        std::cout << "JobB complete\n";
      }
    }
  }
};

int main() {
  JobScheduler scheduler;
  scheduler.insertJob(std::make_unique<JobA>());
  scheduler.insertJob(std::make_unique<JobB>(20));

  while (scheduler.numActive() > 0) {
    scheduler.executeAll();
  }
}