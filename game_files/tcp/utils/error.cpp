#include "error.hpp"

namespace tcp {

//!
//! ctor & dtor
//!

tcp_error::tcp_error(const std::string& what, const std::string& file, std::size_t line)
: std::runtime_error(what)
, m_file(file)
, m_line(line) {}

//!
//! get location of the error
//!

const std::string&
tcp_error::get_file(void) const {
  return m_file;
}

std::size_t
tcp_error::get_line(void) const {
  return m_line;
}

} // namespace tcp
