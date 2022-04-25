# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 3.0)
find_package(Rock)
project(rock_tutorial VERSION 0.1 DESCRIPTION "Rock Tutorial")
rock_init()
rock_standard_layout()
