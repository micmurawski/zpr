#pragma once

#include "../utils/typedefs.hpp"

namespace tcp {
class self_pipe {
public:
  self_pipe(void);
  ~self_pipe(void);
  self_pipe(const self_pipe&) = delete;
  self_pipe& operator=(const self_pipe&) = delete;

public:
  fd_t get_read_fd(void) const;
  fd_t get_write_fd(void) const;
  void notify(void);
  void clr_buffer(void);

private:
#ifdef _WIN32
  fd_t m_fd;
  struct sockaddr m_addr;

  int m_addr_len;
#else
  fd_t m_fds[2];
#endif /* _WIN32 */
};

}
