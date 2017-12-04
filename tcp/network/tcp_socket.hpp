#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../utils/typedefs.hpp"

namespace tcp {

class tcp_socket {
public:
  enum class type {
    CLIENT,
    SERVER,
    UNKNOWN
  };

public:
  tcp_socket(void);
  ~tcp_socket(void) = default;
  tcp_socket(fd_t fd, const std::string& host, std::uint32_t port, type t);
 tcp_socket(tcp_socket&&);
  tcp_socket(const tcp_socket&) = delete;
  tcp_socket& operator=(const tcp_socket&) = delete;

public:
  bool operator==(const tcp_socket& rhs) const;
  bool operator!=(const tcp_socket& rhs) const;

public:

  std::vector<char> recv(std::size_t size_to_read);
  std::size_t send(const std::vector<char>& data, std::size_t size_to_write);
  void connect(const std::string& host, std::uint32_t port, std::uint32_t timeout_msecs = 0);
  void bind(const std::string& host, std::uint32_t port);
  void listen(std::size_t max_connection_queue);
  tcp_socket accept(void);
  void close(void);

public:
  const std::string& get_host(void) const;
  std::uint32_t get_port(void) const;
  type get_type(void) const;
  void set_type(type t);
  fd_t get_fd(void) const;

public:
  bool is_ipv6(void) const;

private:
  void create_socket_if_necessary(void);
  void check_or_set_type(type t);

private:
  fd_t m_fd;
  std::string m_host;
  std::uint32_t m_port;
  type m_type;
};

}
