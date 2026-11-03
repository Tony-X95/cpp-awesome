cmake_minimum_required(VERSION 3.15)

project(P_C VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Producer_Consumer Producer_Consumer.cpp)