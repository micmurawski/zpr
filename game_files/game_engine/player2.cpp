#include <condition_variable>
#include <iostream>
#include <mutex>
#include <signal.h>
#include "game_client.hpp"
#include <signal.h>

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

  //GameClient gameClient;
  GameClient::get()._name="Player2";
  GameClient::get().connect("127.0.0.1",3002);
  GameClient::get().sendCmd("<join>gra1</join>");
  signal(SIGINT, &signint_handler);
  std::mutex mtx;
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);

#ifdef _WIN32
  WSACleanup();
#endif /* _WIN32 */

  return 0;
}
