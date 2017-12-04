env = Environment()
target = ['tcp_server','tcp_client','tcp_client2']
sources = ['tcp_server.cpp','tcp_client.cpp','tcp_client2.cpp']
includesPaths = ['-ltcp']
cxxflags=['-std=c++11']
tcp_source =[
        'tcp/network/io_service.cpp',
        'tcp/network/tcp_client.cpp',
        'tcp/network/tcp_server.cpp',
        'tcp/network/common/tcp_socket.cpp',
        'tcp/network/unix/unix_self_pipe.cpp',
        'tcp/network/unix/unix_tcp_socket.cpp',
        'tcp/network/windows/windows_self_pipe.cpp',
        'tcp/network/windows/windows_tcp_socket.cpp',
        'tcp/utils/error.cpp',
        'tcp/utils/logger.cpp',
        'tcp/utils/thread_pool.cpp'
]
env.Library('tcp',
tcp_source,
LINKFLAGS=  ['-lpthread','-pthread'],
CXXFLAGS=cxxflags)
env.Program(target = target[0],
        source = sources[0],
        LINKFLAGS=  ['-lpthread','-pthread'],
        LIBS=['tcp'],
        LIBPATH='.',
        CXXFLAGS = cxxflags);
env.Program(target = target[1],
        source = sources[1],
        LINKFLAGS=  ['-lpthread','-pthread'],
        LIBS=['tcp'],
        LIBPATH='.',
        CXXFLAGS = cxxflags);
env.Program(target = target[2],
        source = sources[2],
        LINKFLAGS=  ['-lpthread','-pthread'],
        LIBS=['tcp'],
        LIBPATH='.',
        CXXFLAGS = cxxflags);