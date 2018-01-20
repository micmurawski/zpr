#include "mainwindow.hpp"
#include <QApplication>
#include "../game_files/game_engine/game_client.hpp"

int main(int argc, char *argv[])
{
    if(argc==1){
        std::cout<<"Proszę podać argumenty"<<std::endl;
        std::cout<<"Przykłady"<<std::endl;
        std::cout<<"-c #host #port #player_name #game_name - tworzy instancje gry na serwerze"<<std::endl;
        std::cout<<"-l #host #port #player_name - wyświetla listę dostępnych gier"<<std::endl;
        std::cout<<"-j #host #port #player_name #game_name - dołącza do gry"<<std::endl;

        return 1;
    }
    std::string cmd(argv[1]);
    if (cmd=="-c"){
        GameClient::getInstance()._name=argv[4];
        GameClient::getInstance().connect(std::string(argv[2]),atoi(argv[3]));
        GameClient::getInstance().sendCmd("<create>"+std::string(argv[5])+"</create>");
        std::cout<<"Oczekiwanie..."<<std::endl;
        while(GameClient::getInstance().getState()); //Oczekiwanie na inicjalizacje gry
    }else if(cmd=="-j"){
        GameClient::getInstance()._name=argv[4];
        GameClient::getInstance().connect(std::string(argv[2]),atoi(argv[3]));
        GameClient::getInstance().sendCmd("<join>"+std::string(argv[5])+"</join>");
        while(GameClient::getInstance().getState()); //Oczekiwanie na inicjalizacje gry
    }else if(cmd=="-l"){
        GameClient::getInstance()._name=argv[4];
        GameClient::getInstance().connect(std::string(argv[2]),atoi(argv[3]));
        getchar();
        return 0;
    }else{
        return 1;
    }

    std::cout<<"Uruchomienie UI"<<std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
