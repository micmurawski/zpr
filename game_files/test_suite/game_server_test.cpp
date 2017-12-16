#include "../game_engine/game_server.hpp"
#include "../game_engine/game_engine.hpp"
#include <iostream>
#include <signal.h>
#include <condition_variable>


std::condition_variable cv;

void signint_handler(int) {
  cv.notify_all();
}

int main(void) {
  #ifdef _WIN32
  //! Windows netword DLL init
  WORD version = MAKEWORD(2, 2);
  WSADATA data;

  if (WSAStartup(version, &data) != 0) {
    std::cerr << "WSAStartup() failure" << std::endl;
    return -1;
  }
#endif /* _WIN32 */
GameServer::get().start("127.0.0.1",3002);

  signal(SIGINT, &signint_handler);
  std::mutex mtx;
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);

#ifdef _WIN32
  WSACleanup();
#endif /* _WIN32 */

  return 0;
}
