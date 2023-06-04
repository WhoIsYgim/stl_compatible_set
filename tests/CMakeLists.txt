project(set_tests)
find_package(GTest REQUIRED)

file(GLOB TEST_SOURCES "test_*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})
add_executable(base_test base_test_set.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest_main)
target_link_libraries(${PROJECT_NAME} PUBLIC set)
target_link_libraries(base_test       PUBLIC set)

gtest_discover_tests(${PROJECT_NAME})
