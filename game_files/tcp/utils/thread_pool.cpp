#include "logger.hpp"
#include "thread_pool.hpp"

namespace tcp {

namespace utils {

//!
//! ctor & dtor
//!

thread_pool::thread_pool(std::size_t nb_threads) {
  __TCP_LOG(debug, "create thread_pool");
  set_nb_threads(nb_threads);
}

thread_pool::~thread_pool(void) {
  __TCP_LOG(debug, "destroy thread_pool");
  stop();
}

//!
//! worker main loop
//!

void
thread_pool::run(void) {
  __TCP_LOG(debug, "start run() worker");

  while (true) {
    auto res     = fetch_task_or_stop();
    bool stopped = res.first;
    task_t task  = res.second;

    //! if thread has been requested to stop, stop it here
    if (stopped) {
      break;
    }

    //! execute task
    if (task) {
      __TCP_LOG(debug, "execute task");

      try {
        task();
      }
      catch (const std::exception&) {
        __TCP_LOG(warn, "uncatched exception propagated up to the threadpool.")
      }

      __TCP_LOG(debug, "execution complete");
    }
  }

  __TCP_LOG(debug, "stop run() worker");
}

//!
//! stop the thread pool and wait for workers completion
//!

void
thread_pool::stop(void) {
  if (!is_running()) { return; }

  m_should_stop = true;
  m_tasks_condvar.notify_all();

  for (auto& worker : m_workers) { worker.join(); }

  m_workers.clear();

  __TCP_LOG(debug, "thread_pool stopped");
}

//!
//! whether the thread_pool is running or not
//!
bool
thread_pool::is_running(void) const {
  return !m_should_stop;
}

//!
//! whether the current thread should stop or not
//!
bool
thread_pool::should_stop(void) const {
  return m_should_stop || m_nb_running_threads > m_max_nb_threads;
}

//!
//! retrieve a new task
//!

std::pair<bool, thread_pool::task_t>
thread_pool::fetch_task_or_stop(void) {
  std::unique_lock<std::mutex> lock(m_tasks_mtx);

  __TCP_LOG(debug, "waiting to fetch task");

  m_tasks_condvar.wait(lock, [&] { return should_stop() || !m_tasks.empty(); });

  if (should_stop()) {
    --m_nb_running_threads;
    return {true, nullptr};
  }

  task_t task = std::move(m_tasks.front());
  m_tasks.pop();
  return {false, task};
}

//!
//! add tasks to thread pool
//!

void
thread_pool::add_task(const task_t& task) {
  std::lock_guard<std::mutex> lock(m_tasks_mtx);

  __TCP_LOG(debug, "add task to thread_pool");

  m_tasks.push(task);
  m_tasks_condvar.notify_all();
}

thread_pool&
thread_pool::operator<<(const task_t& task) {
  add_task(task);

  return *this;
}

//!
//! adjust number of threads
//!
void
thread_pool::set_nb_threads(std::size_t nb_threads) {
  m_max_nb_threads = nb_threads;

  //! if we increased the number of threads, spawn them
  while (m_nb_running_threads < m_max_nb_threads) {
    ++m_nb_running_threads;
    m_workers.push_back(std::thread(std::bind(&thread_pool::run, this)));
  }

  //! otherwise, wake up threads to make them stop if necessary (until we get the right amount of threads)
  if (m_nb_running_threads > m_max_nb_threads) {
    m_tasks_condvar.notify_all();
  }
}

} // namespace utils

} // namespace tcp
