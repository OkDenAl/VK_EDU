cmake_minimum_required(VERSION 3.14)
project(test_parser)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-coverage)

file(GLOB SOURCES *.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CALCULATOR_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CALCULATOR_LIBRARIES} GTest::GTest)

add_test(test_parser test_parser)