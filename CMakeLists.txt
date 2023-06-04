cmake_minimum_required(VERSION 3.23.2)
project(set LANGUAGES CXX)


option(BUILD_EXAMPLE_1 "Build executable example #1." ON)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wnon-virtual-dtor")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")


SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -lgcov")

add_library(${PROJECT_NAME} INTERFACE )
target_include_directories(${PROJECT_NAME} INTERFACE include)

if (BUILD_EXAMPLE_1)
    add_executable(example_1 examples/example_1.cpp)
    target_link_libraries(example_1 ${PROJECT_NAME})
endif ()

enable_testing()
add_subdirectory(tests)
