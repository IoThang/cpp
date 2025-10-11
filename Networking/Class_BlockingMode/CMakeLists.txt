# Specify the minimum version of CMake required
cmake_minimum_required (VERSION 3.20)

# Specify the MinGW compiler
set(CMAKE_CXX_COMPILER "C:/Tools/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.7-mingw-w64ucrt-12.0.0-r3/mingw64/bin/x86_64-w64-mingw32-g++.exe")

# Define the project name and language
project("networking" LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    set(WINSOCK_LIB ws2_32)
endif()
#===================== server =============================================
# Add the executable
add_executable(client inc/TcpClient.h src/TcpClient.cpp src/client_main.cpp)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Optionally, link libraries (uncomment if you use external libraries)
target_link_libraries(client ${WINSOCK_LIB})
#===================== client =============================================
# Add the executable
add_executable(server inc/TcpServer.h src/TcpServer.cpp src/server_main.cpp)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Optionally, link libraries (uncomment if you use external libraries)
target_link_libraries(server ${WINSOCK_LIB})