

#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <Winsock2.h>
#else
#include <sys/select.h>
#endif /* _WIN32 */

#include "self_pipe.hpp"
#include "tcp_socket.hpp"
#include "../utils/thread_pool.hpp"

#ifndef __TCP_IO_SERVICE_NB_WORKERS
#define __TCP_IO_SERVICE_NB_WORKERS 1
#endif /* __TCP_IO_SERVICE_NB_WORKERS */

namespace tcp {
class io_service {
public:
  io_service(void);
  ~io_service(void);
  io_service(const io_service&) = delete;
  io_service& operator=(const io_service&) = delete;

public:
  void set_nb_workers(std::size_t nb_threads);

public:
  typedef std::function<void(fd_t)> event_callback_t;
  void track(const tcp_socket& socket, const event_callback_t& rd_callback = nullptr, const event_callback_t& wr_callback = nullptr);
  void set_rd_callback(const tcp_socket& socket, const event_callback_t& event_callback);
  void set_wr_callback(const tcp_socket& socket, const event_callback_t& event_callback);
  void untrack(const tcp_socket& socket);
  void wait_for_removal(const tcp_socket& socket);

private:
  struct tracked_socket {
    
    tracked_socket(void)
    : rd_callback(nullptr)
    , wr_callback(nullptr) {}
    event_callback_t rd_callback;
    std::atomic<bool> is_executing_rd_callback = ATOMIC_VAR_INIT(false);
    event_callback_t wr_callback;
    std::atomic<bool> is_executing_wr_callback = ATOMIC_VAR_INIT(false);
    std::atomic<bool> marked_for_untrack = ATOMIC_VAR_INIT(false);
  };

private:
  void poll(void);
  int init_poll_fds_info(void);
  void process_events(void);
  void process_rd_event(const fd_t& fd, tracked_socket& socket);
  void process_wr_event(const fd_t& fd, tracked_socket& socket);

private:
  std::unordered_map<fd_t, tracked_socket> m_tracked_sockets;
  std::atomic<bool> m_should_stop;
  std::thread m_poll_worker;
  utils::thread_pool m_callback_workers;
  std::mutex m_tracked_sockets_mtx;
  std::vector<fd_t> m_polled_fds;
  fd_set m_rd_set;
  fd_set m_wr_set;
  std::condition_variable m_wait_for_removal_condvar;
  tcp::self_pipe m_notifier;
};
const std::shared_ptr<io_service>& get_default_io_service(void);
void set_default_io_service(const std::shared_ptr<io_service>& service);

}
