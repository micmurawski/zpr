#include "game_server.hpp"
#include "game_engine.hpp"
#include <iostream>
#include <signal.h>
#include <condition_variable>


std::condition_variable cv;

void signint_handler(int) {
  cv.notify_all();
}

int main(int argc, char *argv[]) {

  if(argc==1){
        GameServer::getInstance().start("127.0.0.1",3002);

        }else{
    std::string cmd(argv[1]);
    if (cmd=="-h"){
        std::cout<<"Proszę podać argumenty"<<std::endl;
        std::cout<<"Przykłady"<<std::endl;
        std::cout<<"server -s #host #port "<<std::endl;
    }else if(cmd=="-s"){
        GameServer::getInstance().start(argv[2],atoi(argv[3]));
    }else{
       //GameServer::getInstance().start("127.0.0.1",3002);

    }}


  signal(SIGINT, &signint_handler);
  std::mutex mtx;
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);



  return 0;
}
