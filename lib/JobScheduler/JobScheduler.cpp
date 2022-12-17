#include "JobScheduler.hpp"

#include <algorithm>

// namespace job_manager {

void JobScheduler::executeAll(void) {
  for (auto& j : jobs) {
    if (j) {
      j->execute();

      // Remove job from array if job is complete
      if (j->isComplete()) {
        j.reset();
      }
    }
  }
}

void JobScheduler::insertJob(std::unique_ptr<Job> job) {
  for (auto& j : jobs) {
    if (!j) {
      j = std::move(job);
      break;
    }
  }
}

int JobScheduler::numActive(void) {
  return std::count_if(jobs.begin(), jobs.end(),
                       [](auto& job) { return job != nullptr; });
}

bool JobScheduler::isFull(void) { return numActive() == MAX_JOBS; }
// };  // namespace job_manager
