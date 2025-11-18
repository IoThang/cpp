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
        src/Socket.cpp
        src/Epoll.cpp
        src/ClientHandler.cpp
        src/ServerHandler.cpp
        src/ServerStdinHandler.cpp
        src/EpollServer.cpp
        src/server_main.cpp
        inc/DefaultTaskProcessor.h
        inc/Task.h
        src/Task.cpp
        src/Thread.cpp
        src/ThreadPool.cpp
        src/DefaultTaskProcessor.cpp
)

add_executable(client
        src/Socket.cpp
        src/Epoll.cpp
        src/ClientHandler.cpp
        src/ClientSocketHandler.cpp
        src/ClientStdinHandler.cpp
        src/EpollClient.cpp
        src/client_main.cpp
        inc/DefaultTaskProcessor.h
        inc/Task.h
        src/Task.cpp
        inc/Thread.h
        src/Thread.cpp
        inc/ThreadPool.h
        src/ThreadPool.cpp
        src/DefaultTaskProcessor.cpp
)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
