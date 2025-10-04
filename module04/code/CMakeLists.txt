# Specify the minimum version of CMake required
cmake_minimum_required (VERSION 3.20)

# Specify the MinGW compiler
set(CMAKE_CXX_COMPILER "C:/toolbase/mingw/test25_comp_8.1.0_testversion/bin/g++.exe")

# Define the project name and language
project("ex01" LANGUAGES CXX)


# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Add the executable
add_executable(main
        inc/Factory.h
        inc/Animal.h
        inc/Dog.h
        inc/Cat.h
        inc/Brain.h
        src/Factory.cpp
        src/Animal.cpp
        src/main.cpp
        src/Dog.cpp
        src/Cat.cpp
        src/Brain.cpp)

# Optionally, specify include directories (uncomment if you have header files)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Optionally, link libraries (uncomment if you use external libraries)
# target_link_libraries(myprogram PRIVATE some_library)