cmake_minimum_required(VERSION 3.20)

project(GravitySimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)

add_executable(GravitySimulator
    src/main.cpp
    src/Body.cpp
    src/Physics.cpp
    src/Renderer.cpp
    src/Simulation.cpp
)

target_include_directories(GravitySimulator PRIVATE include)

target_link_libraries(GravitySimulator PRIVATE SDL2::SDL2)

target_compile_options(GravitySimulator PRIVATE
    -Wall
    -Wextra
    -O2
)
