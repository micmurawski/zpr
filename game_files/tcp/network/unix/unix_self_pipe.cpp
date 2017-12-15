#ifndef _WIN32

#include "../self_pipe.hpp"
#include "../../utils/error.hpp"

#include <fcntl.h>
#include <unistd.h>

namespace tcp {

//!
//! ctor & dtor
//!
self_pipe::self_pipe(void)
: m_fds{__TCP_INVALID_FD, __TCP_INVALID_FD} {
  if (pipe(m_fds) == -1) { __TCP_THROW(error, "pipe() failure"); }
}

self_pipe::~self_pipe(void) {
  if (m_fds[0] != __TCP_INVALID_FD) {
    close(m_fds[0]);
  }

  if (m_fds[1] != __TCP_INVALID_FD) {
    close(m_fds[1]);
  }
}

//!
//! get rd/wr fds
//!
fd_t
self_pipe::get_read_fd(void) const {
  return m_fds[0];
}

fd_t
self_pipe::get_write_fd(void) const {
  return m_fds[1];
}

//!
//! notify
//!
void
self_pipe::notify(void) {
  (void) write(m_fds[1], "a", 1);
}

//!
//! clr buffer
//!
void
self_pipe::clr_buffer(void) {
  char buf[1024];
  (void) read(m_fds[0], buf, 1024);
}

} // namespace tcp

#endif /* _WIN32 */
