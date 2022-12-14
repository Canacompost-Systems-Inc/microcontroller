#ifndef JOB_SCHEDULER
#define JOB_SCHEDULER

#include <array>

// namespace job_manager {

// I don't expect a large number will be needed.
#define MAX_JOBS 4


// Users can define any job they wish by inheriting this.
class Job {
 public:
  virtual void execute(void) = 0;
  virtual bool isComplete(void) = 0;
};



class JobScheduler {
 private:
  // Wrapper class allows for users to define jobs anywhere and the
  // JobScheduler doesn't care.
  class JobWrapper {
   private:
    Job* currJob;
    bool active;

   public:
    JobWrapper(void) : currJob{NULL}, active{false} {}

    /**
     * @brief Sets currentJob and changes state to active.
     *
     * @param job Pointer to new job.
     *
     * @warning Will overwrite previous job regardless of its status.
     *
     * @todo Maybe change this to use unique_ptr so users dont have to maintain
     * jobs outside the JobScheduler.
     */
    void setJob(Job* job) {
      currJob = job;
      active = true;
    }

	/**
	 * @brief Indicates there is a job ready to execute.
	 */
    bool isActive(void) { return active; }

    /**
     * @brief Executes the current job and sets active status to false if
     * complete.
     */
    void execute(void) {
      currJob->execute();
      if (currJob->isComplete()) {
        active = false;
      }
    }
  };

//   TODO: Change this to use the projects custom array.
  std::array<JobWrapper, MAX_JOBS> jobs;

 public:
	/**
	 * @brief Construct a new JobScheduler object
	 */
	JobScheduler(void) {}

 /**
  * @brief Execute all active jobs.
  */
  void executeAll(void);

  /**
   * @brief Insert job into the manager to be executed.
   * 
   * @param job Job to insert.
   */
  void insertJob(Job* job);

  /**
   * @brief Counts the number of active jobs.
   * 
   * @return int 
   */
  int numActive(void);

  /**
   * @brief Indicates if there is room for another Job.
   * 
   * @return true Job Scheduler is full of active jobs.
   * @return false There are some inactive or completed jobs.
   */
  bool isFull(void);
};
// };  // namespace job_manager
#endif