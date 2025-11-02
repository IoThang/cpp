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
add_executable(client
        inc/ISocket.h
        inc/TCPSocket.h
        inc/SocketFactory.h
        inc/Server.h
        src/SocketFactory.cpp
        src/TCPSocket.cpp
        src/Server.cpp
        src/server_main.cpp
        src/client.cpp
        inc/client.h
        src/client_main.cpp
)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)


