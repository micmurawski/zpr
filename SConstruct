import os
env = Environment()
LIBPATH = ['game_files/libs/.']
cxxflags=['-std=c++17']
LIBS=['tcp','boost_regex']
LINKFLAGS=  ['-lpthread','-pthread']
tcp_source =[
        'game_files/tcp/network/io_service.cpp',
        'game_files/tcp/network/tcp_client.cpp',
        'game_files/tcp/network/tcp_server.cpp',
        'game_files/tcp/network/common/tcp_socket.cpp',
        'game_files/tcp/network/unix/unix_self_pipe.cpp',
        'game_files/tcp/network/unix/unix_tcp_socket.cpp',
        'game_files/tcp/network/windows/windows_self_pipe.cpp',
        'game_files/tcp/network/windows/windows_tcp_socket.cpp',
        'game_files/tcp/utils/error.cpp',
        'game_files/tcp/utils/logger.cpp',
        'game_files/tcp/utils/thread_pool.cpp'
]
print("KOMPILACJA BIBLIOTEKI TCP")
env.Library('game_files/libs/tcp',
tcp_source,
LINKFLAGS=LINKFLAGS,
CXXFLAGS=cxxflags)
print("KOMPILACJA SERWERA")
env.Program(target = ['server'],
        source = [
        'game_files/game_engine/game_server_test.cpp',
        'game_files/game_engine/game_engine.cpp',
        'game_files/game_engine/game_server.cpp',
        'game_files/game_state/game_state.cpp',
        'game_files/game_objects/map_point.cpp',
        'game_files/game_objects/player.cpp',
        'game_files/game_objects/building.cpp',
        'game_files/game_objects/ship.cpp',
        'game_files/game_objects/resources.cpp',
        'game_files/game_state/map_generator.cpp'],
        LINKFLAGS=LINKFLAGS,
        LIBS=LIBS,
        LIBPATH=LIBPATH,
        CXXFLAGS = cxxflags);