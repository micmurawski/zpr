env = Environment()
target = ['tcp_server','tcp_client','tcp_client2']
sources = ['tcp_server.cpp','tcp_client.cpp','tcp_client2.cpp']
includesPaths = ['-ltacopie']
cxxflags=['-std=c++11']
tacopie_source =[
        'tacopie/network/io_service.cpp',
        'tacopie/network/tcp_client.cpp',
        'tacopie/network/tcp_server.cpp',
        'tacopie/network/common/tcp_socket.cpp',
        'tacopie/network/unix/unix_self_pipe.cpp',
        'tacopie/network/unix/unix_tcp_socket.cpp',
        'tacopie/network/windows/windows_self_pipe.cpp',
        'tacopie/network/windows/windows_tcp_socket.cpp',
        'tacopie/utils/error.cpp',
        'tacopie/utils/logger.cpp',
        'tacopie/utils/thread_pool.cpp'
        
]
env.Library('tacopie',
tacopie_source,
LINKFLAGS=  ['-lpthread','-pthread'],
CXXFLAGS=cxxflags)
env.Program(target = target[0],
        source = sources[0],
        LINKFLAGS=  ['-lpthread','-pthread'],
        LIBS=['tacopie'],
        LIBPATH='.',
        CXXFLAGS = cxxflags);
env.Program(target = target[1],
        source = sources[1],
        LINKFLAGS=  ['-lpthread','-pthread'],
        LIBS=['tacopie'],
        LIBPATH='.',
        CXXFLAGS = cxxflags);
env.Program(target = target[2],
        source = sources[2],
        LINKFLAGS=  ['-lpthread','-pthread'],
        LIBS=['tacopie'],
        LIBPATH='.',
        CXXFLAGS = cxxflags);