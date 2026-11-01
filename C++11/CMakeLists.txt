cmake_minimum_required(VERSION 3.15)

project(Obs_Sub VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Obs_Sub Observer_Subject.cpp)

