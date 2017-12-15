#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

#include "logger.hpp"

namespace tcp {

//!
//! specialized runtime_error used for tcp error
//!
class tcp_error : public std::runtime_error {
public:
  //! ctor
  tcp_error(const std::string& what, const std::string& file, std::size_t line);
  //! assignment operator
  ~tcp_error(void) = default;

  //! copy ctor
  tcp_error(const tcp_error&) = default;
  //! assignment operator
  tcp_error& operator=(const tcp_error&) = default;

public:
  //!
  //! \return file in which error occured
  //!
  const std::string& get_file(void) const;

  //!
  //! \return line at which the error occured
  //!
  std::size_t get_line(void) const;

private:
  //!
  //! file location of the error
  //!
  std::string m_file;

  //!
  //! line location of the error
  //!
  std::size_t m_line;
};

} // namespace tcp

//! macro for convenience
#define __TCP_THROW(level, what)                          \
  {                                                           \
    __TCP_LOG(level, (what));                             \
    throw tcp::tcp_error((what), __FILE__, __LINE__); \
  }
