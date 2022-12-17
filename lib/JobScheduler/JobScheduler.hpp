#ifndef JOB_SCHEDULER
#define JOB_SCHEDULER

#include <array>
#include <memory>

// namespace job_manager {

// I don't expect a large number will be needed.
#define MAX_JOBS 4

// Users can define any job they wish by inheriting this.
class Job {
 public:
  virtual void execute(void) = 0;
  virtual bool isComplete(void) = 0;
  virtual ~Job(void) = default;
};

class JobScheduler {
 private:
  // TODO: Maybe change this to use the projects custom array.
  std::array<std::unique_ptr<Job>, MAX_JOBS> jobs;

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
  void insertJob(std::unique_ptr<Job> job);

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