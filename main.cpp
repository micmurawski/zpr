//#include "client_window.hpp"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    ClientWindow w;
//    w.show();

//    return a.exec();

//}

#include "game_files/game_sendable.hpp"
#include <cstdio>
#include <iostream>
int main(){
    GameSendable g;
    g.body_length(12);
    g.SetType(3);
    std::memcpy(g.body(), "abcdefghijwq", g.body_length()+1);
    g.encode_header();
    std::cout <<g.data();
    return 0;
}

