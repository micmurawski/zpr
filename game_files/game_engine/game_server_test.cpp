#include "game_server.hpp"
#include "game_engine.hpp"
#include <iostream>
#include <signal.h>
#include <condition_variable>


std::condition_variable cv;

void signint_handler(int) {
  cv.notify_all();
}

int main(void) {
GameServer::getInstance().start("127.0.0.1",3002);

  signal(SIGINT, &signint_handler);
  std::mutex mtx;
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);



  return 0;
}
