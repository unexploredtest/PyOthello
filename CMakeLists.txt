cmake_minimum_required(VERSION 3.4)
project(PyOthello)

add_subdirectory(external/pybind11)
pybind11_add_module(PyOthello src/PyOthello.cpp src/Othello.cpp src/OthelloSolver.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(PyOthello
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})