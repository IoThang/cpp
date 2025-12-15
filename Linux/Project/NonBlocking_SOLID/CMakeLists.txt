# Specify the minimum version of CMake required
cmake_minimum_required (VERSION 3.20)

# Specify the MinGW compiler
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Define the project name and language
project("networking" LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the executable
add_executable(server
        ImplementationSet/Infrastructure/src/Socket.cpp
        ImplementationSet/Infrastructure/src/Epoll.cpp
        ImplementationSet/Server/src/ClientHandler.cpp
        ImplementationSet/Server/src/ServerHandler.cpp
        ImplementationSet/Server/src/ServerStdinHandler.cpp
        ImplementationSet/Server/src/EpollServer.cpp
        ImplementationSet/Server/src/server_main.cpp
        inc/DefaultTaskProcessor.h
        inc/Task.h
        ImplementationSet/Infrastructure/src/Task.cpp
        ImplementationSet/Infrastructure/src/Thread.cpp
        ImplementationSet/Infrastructure/src/ThreadPool.cpp
        ImplementationSet/Infrastructure/src/DefaultTaskProcessor.cpp
        ImplementationSet/Client/src/ClientRegistry.cpp
        ImplementationSet/Client/src/ClientInfo.cpp
        inc/ClientInfoFactory.h
        ImplementationSet/Client/src/ClientInfoFactory.cpp
        ImplementationSet/Server/src/ClientHandler.cpp
)

add_executable(client
        ImplementationSet/Infrastructure/src/Socket.cpp
        ImplementationSet/Infrastructure/src/Epoll.cpp
        ImplementationSet/Client/src/ClientSocketHandler.cpp
        ImplementationSet/Client/src/ClientStdinHandler.cpp
        ImplementationSet/Client/src/EpollClient.cpp
        ImplementationSet/Client/src/client_main.cpp
        inc/Task.h
        ImplementationSet/Infrastructure/src/Task.cpp
        inc/Thread.h
        ImplementationSet/Infrastructure/src/Thread.cpp
        inc/ThreadPool.h
        ImplementationSet/Infrastructure/src/ThreadPool.cpp
        inc/IObserver.h
        inc/ISubject.h
)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
