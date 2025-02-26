cmake_minimum_required(VERSION 3.28)
project(path_solver)

set(CMAKE_CXX_STANDARD 17)

add_executable(path_solver main.cpp
        PathSolver.cpp
        NodeList.cpp
        Node.cpp
        milestone4.h)
