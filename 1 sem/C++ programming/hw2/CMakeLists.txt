cmake_minimum_required(VERSION 3.0.0)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_link_options(-coverage -lgcov)

enable_testing()
add_subdirectory(project)

add_executable(${PROJECT_NAME} main.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC ${CALCULATOR_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CALCULATOR_LIBRARIES})

add_subdirectory(tests)