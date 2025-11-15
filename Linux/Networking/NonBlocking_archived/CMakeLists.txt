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
add_executable(nonblocking
        inc/ISocket.h
        inc/IEventHandler.h
        inc/TCPSocket.h
        src/TCPSocket.cpp

)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(nonblocking PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)