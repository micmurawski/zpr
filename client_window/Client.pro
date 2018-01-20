#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T16:30:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mapview.cpp \
    mappoint.cpp \
    leftbar.cpp \
    rightbar.cpp \
    bottombar.cpp \
    ../game_files/game_engine/game_client.cpp \
    ../game_files/game_objects/game_object_factory.cpp \
    ../game_files/game_objects/map_point.cpp \
    ../game_files/game_objects/resources.cpp \
    ../game_files/game_objects/ship.cpp \
    ../game_files/game_order/game_order.cpp \
    ../game_files/game_state/game_state.cpp \
    playerscolors.cpp \
    planetdetails.cpp \
    ../game_files/game_objects/building.cpp \
    ../game_files/game_objects/player.cpp


HEADERS += \
        mainwindow.hpp \
    mapview.hpp \
    mappoint.hpp \
    leftbar.hpp \
    rightbar.hpp \
    bottombar.hpp \
    ../game_files/game_engine/game_client.hpp \
    ../game_files/game_objects/building.hpp \
    ../game_files/game_objects/game_object.hpp \
    ../game_files/game_objects/game_object_factory.hpp \
    ../game_files/game_objects/map_point.hpp \
    ../game_files/game_objects/player.hpp \
    ../game_files/game_objects/resources.hpp \
    ../game_files/game_objects/ship.hpp \
    ../game_files/game_order/game_order.hpp \
    ../game_files/game_order/order_decoder.hpp \
    ../game_files/game_state/game_state.hpp \
    ../game_files/typedefs.hpp \
    playerscolors.hpp \
    planetdetails.hpp \
    ../game_files/get_regex_function.hpp


FORMS += \
        mainwindow.ui
LIBS += -L -libgame.a
LIBS += -L -lboost_regex
LIBS += -L$$PWD/../game_files/libs/ -ltcp
CONFIG +=c++17
QMAKE_CXXFLAGS += -std=c++17


