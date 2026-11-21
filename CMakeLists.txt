cmake_minimum_required(VERSION 3.24)

project(CellularAutomata LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

add_executable(CellularAutomata
    src/main.cpp
    src/core/Grid.cpp
    src/simulation/Automaton.cpp
    src/rendering/Renderer.cpp
)

target_include_directories(CellularAutomata PRIVATE src)
target_link_libraries(CellularAutomata PRIVATE raylib)
