#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


namespace tcp {

namespace utils {

//!
//! basic thread pool used to push async tasks from the io_service
//!
class thread_pool {
public:
  //!
  //! ctor
  //! created the worker thread that start working immediately
  //!
  //! \param nb_threads number of threads to start the thread pool
  //!
  explicit thread_pool(std::size_t nb_threads);

  //! dtor
  ~thread_pool(void);

  //! copy ctor
  thread_pool(const thread_pool&) = delete;
  //! assignment operator
  thread_pool& operator=(const thread_pool&) = delete;

public:
  //!
  //! task typedef
  ///! simply a callable taking no parameter
  //!
  typedef std::function<void()> task_t;

  //!
  //! add tasks to thread pool
  //! task is enqueued and will be executed whenever all previously executed tasked have been executed (or are currently being executed)
  //!
  //! \param task task to be executed by the threadpool
  //!
  void add_task(const task_t& task);

  //!
  //! same as add_task
  //!
  //! \param task task to be executed by the threadpool
  //! \return current instance
  //!
  thread_pool& operator<<(const task_t& task);

  //!
  //! stop the thread pool and wait for workers completion
  //! if some tasks are pending, they won't be executed
  //!
  void stop(void);

public:
  //!
  //! \return whether the thread_pool is running or not
  //!
  bool is_running(void) const;

public:
  //!
  //! reset the number of threads working in the thread pool
  //! this can be safely called at runtime and can be useful if you need to adjust the number of workers
  //!
  //! this function returns immediately, but change might be applied in the background
  //! that is, increasing number of threads will spwan new threads directly from this function (but they may take a while to start)
  //! moreover, shrinking the number of threads can only be applied in the background to make sure to not stop some threads in the middle of their task
  //!
  //! changing number of workers do not affect tasks to be executed and tasks currently being executed
  //!
  //! \param nb_threads number of threads
  //!
  void set_nb_threads(std::size_t nb_threads);

private:
  //!
  //! worker main loop
  //!
  void run(void);

  //!
  //! retrieve a new task
  //! fetch the first element in the queue, or wait if no task are available
  //!
  //! \return a pair <stopped, task>
  //!         pair.first indicated whether the thread has been marked for stop and should return immediately
  //!         pair.second contains the task to be executed
  //!
  std::pair<bool, task_t> fetch_task_or_stop(void);

  //!
  //! \return whether the thread should stop or not
  //!
  bool should_stop(void) const;

private:
  //!
  //! threads
  //!
  std::list<std::thread> m_workers;

  //!
  //! number of threads allowed
  //!
  std::atomic<std::size_t> m_max_nb_threads = ATOMIC_VAR_INIT(0);

  //!
  //! current number of running threads
  //!
  std::atomic<std::size_t> m_nb_running_threads = ATOMIC_VAR_INIT(0);

  //!
  //! whether the thread_pool should stop or not
  //!
  std::atomic<bool> m_should_stop = ATOMIC_VAR_INIT(false);

  //!
  //! tasks
  //!
  std::queue<task_t> m_tasks;

  //!
  //! tasks thread safety
  //!
  std::mutex m_tasks_mtx;

  //!
  //! task condvar to sync on tasks changes
  //!
  std::condition_variable m_tasks_condvar;
};

} // namespace utils

} // namespace tcp
