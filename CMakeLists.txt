cmake_minimum_required(VERSION 3.23.2)

project(set LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE )

target_include_directories(${PROJECT_NAME} INTERFACE include)

add_subdirectory(tests)
