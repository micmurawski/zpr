

#include "tcp_client.hpp"
#include "../utils/error.hpp"
#include "../utils/logger.hpp"

namespace tcp {
tcp_client::tcp_client(void)
: m_disconnection_handler(nullptr) {
  m_io_service = get_default_io_service();
  __TCP_LOG(debug, "create tcp_client");
}

tcp_client::~tcp_client(void) {
  __TCP_LOG(debug, "destroy tcp_client");
  disconnect(true);
}

tcp_client::tcp_client(tcp_socket&& socket)
: m_io_service(get_default_io_service())
, m_socket(std::move(socket))
, m_disconnection_handler(nullptr) {
  m_is_connected = true;
  __TCP_LOG(debug, "create tcp_client");
  m_io_service->track(m_socket);
}

const std::string&
tcp_client::get_host(void) const {
  return m_socket.get_host();
}

std::uint32_t
tcp_client::get_port(void) const {
  return m_socket.get_port();
}

void
tcp_client::connect(const std::string& host, std::uint32_t port, std::uint32_t timeout_msecs) {
  if (is_connected()) { __TCP_THROW(warn, "tcp_client is already connected"); }

  try {
    m_socket.connect(host, port, timeout_msecs);
    m_io_service->track(m_socket);
  }
  catch (const tcp_error& e) {
    m_socket.close();
    throw e;
  }

  m_is_connected = true;

  __TCP_LOG(info, "tcp_client connected");
}

void
tcp_client::disconnect(bool wait_for_removal) {
  if (!is_connected()) { return; }
  m_is_connected = false;
  clear_read_requests();
  clear_write_requests();
  m_io_service->untrack(m_socket);
  if (wait_for_removal) { m_io_service->wait_for_removal(m_socket); }
  m_socket.close();

  __TCP_LOG(info, "tcp_client disconnected");
}
void
tcp_client::clear_read_requests(void) {
  std::lock_guard<std::mutex> lock(m_read_requests_mtx);

  std::queue<read_request> empty;
  std::swap(m_read_requests, empty);
}

void
tcp_client::clear_write_requests(void) {
  std::lock_guard<std::mutex> lock(m_write_requests_mtx);

  std::queue<write_request> empty;
  std::swap(m_write_requests, empty);
}

void
tcp_client::call_disconnection_handler(void) {
  if (m_disconnection_handler) {
    m_disconnection_handler();
  }
}

void
tcp_client::on_read_available(fd_t) {
  __TCP_LOG(info, "read available");

  read_result result;
  auto callback = process_read(result);

  if (!result.success) {
    __TCP_LOG(warn, "read operation failure");
    disconnect();
  }

  if (callback) { callback(result); }

  if (!result.success) { call_disconnection_handler(); }
}


void
tcp_client::on_write_available(fd_t) {
  __TCP_LOG(info, "write available");

  write_result result;
  auto callback = process_write(result);

  if (!result.success) {
    __TCP_LOG(warn, "write operation failure");
    disconnect();
  }

  if (callback) { callback(result); }

  if (!result.success) { call_disconnection_handler(); }
}

tcp_client::async_read_callback_t
tcp_client::process_read(read_result& result) {
  std::lock_guard<std::mutex> lock(m_read_requests_mtx);

  if (m_read_requests.empty()) { return nullptr; }

  const auto& request = m_read_requests.front();
  auto callback       = request.async_read_callback;

  try {
    result.buffer  = m_socket.recv(request.size);
    result.success = true;
  }
  catch (const tcp::tcp_error&) {
    result.success = false;
  }

  m_read_requests.pop();

  if (m_read_requests.empty()) { m_io_service->set_rd_callback(m_socket, nullptr); }

  return callback;
}

tcp_client::async_write_callback_t
tcp_client::process_write(write_result& result) {
  std::lock_guard<std::mutex> lock(m_write_requests_mtx);

  if (m_write_requests.empty()) { return nullptr; }

  const auto& request = m_write_requests.front();
  auto callback       = request.async_write_callback;

  try {
    result.size    = m_socket.send(request.buffer, request.buffer.size());
    result.success = true;
  }
  catch (const tcp::tcp_error&) {
    result.success = false;
  }

  m_write_requests.pop();

  if (m_write_requests.empty()) { m_io_service->set_wr_callback(m_socket, nullptr); }

  return callback;
}

void
tcp_client::async_read(const read_request& request) {
  std::lock_guard<std::mutex> lock(m_read_requests_mtx);

  if (is_connected()) {
    m_io_service->set_rd_callback(m_socket, std::bind(&tcp_client::on_read_available, this, std::placeholders::_1));
    m_read_requests.push(request);
  }
  else {
    __TCP_THROW(warn, "tcp_client is disconnected");
  }
}

void
tcp_client::async_write(const write_request& request) {
  std::lock_guard<std::mutex> lock(m_write_requests_mtx);

  if (is_connected()) {
    m_io_service->set_wr_callback(m_socket, std::bind(&tcp_client::on_write_available, this, std::placeholders::_1));
    m_write_requests.push(request);
  }
  else {
    __TCP_THROW(warn, "tcp_client is disconnected");
  }
}

tcp::tcp_socket&
tcp_client::get_socket(void) {
  return m_socket;
}

const tcp::tcp_socket&
tcp_client::get_socket(void) const {
  return m_socket;
}

const std::shared_ptr<tcp::io_service>&
tcp_client::get_io_service(void) const {
  return m_io_service;
}


void
tcp_client::set_on_disconnection_handler(const disconnection_handler_t& disconnection_handler) {
  m_disconnection_handler = disconnection_handler;
}


bool
tcp_client::is_connected(void) const {
  return m_is_connected;
}

bool
tcp_client::operator==(const tcp_client& rhs) const {
  return m_socket == rhs.m_socket;
}

bool
tcp_client::operator!=(const tcp_client& rhs) const {
  return !operator==(rhs);
}

}
