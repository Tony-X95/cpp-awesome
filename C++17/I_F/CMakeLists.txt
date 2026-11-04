cmake_minimum_required(VERSION 3.15)

project(I_F VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(I_F if_constexpr_fold_expr_main.cpp)