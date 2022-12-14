
#include "JobScheduler.hpp"

#include <algorithm>

// namespace job_manager {

void JobScheduler::executeAll(void) {
  std::for_each(jobs.begin(), jobs.end(), [](auto& jobWrapper) {
    if (jobWrapper.isActive()) {
      jobWrapper.execute();
    }
  });

  // for(auto& job: jobs) {
  // 	if(job.isActive()) {
  // 		job.execute();
  // 	}
  // }
}

void JobScheduler::insertJob(Job* job) {
  if (isFull()) {
    return;
  }
  auto inactiveWrapper = std::find_if(jobs.begin(), jobs.end(),
                               [](auto& jobWrapper) { return !jobWrapper.isActive(); });
  inactiveWrapper->setJob(job);

  // for(auto& j: jobs) {
  //	if(!j.isActive()) {
  //		j.setCurrJob(job);
  //		return true;
  //	}
  // }
  // return false;
}

int JobScheduler::numActive(void) {
  return std::count_if(jobs.begin(), jobs.end(),
                       [](auto& jobWrapper) { return jobWrapper.isActive(); });

  // int count = 0;
  // for(auto& job: jobs) {
  // 	if(job.isActive()) {
  // 		count++;
  // 	}
  // }
  // return count;
}

bool JobScheduler::isFull(void) { return numActive() == MAX_JOBS; }
// };  // namespace job_manager
