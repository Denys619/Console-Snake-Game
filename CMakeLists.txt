cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/field.cpp
    src/food.cpp
    src/random.cpp
    src/snake.cpp
    src/terminal.cpp
)

include_directories(include)

add_executable(SnakeGame ${SOURCES})
