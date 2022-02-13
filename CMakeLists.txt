cmake_minimum_required(VERSION 3.20)
project(nonogram_solver)

set(CMAKE_CXX_STANDARD 17)

add_executable(nonogram_solver main.cpp Field.cpp Field.h Rule.cpp Rule.h)