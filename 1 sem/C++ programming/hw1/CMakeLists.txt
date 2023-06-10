cmake_minimum_required(VERSION 3.0.0)
project(actors_film)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wpedantic")

add_subdirectory(project)

add_executable(${PROJECT_NAME} main.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC ${ACTOR_FILMS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ACTOR_FILMS_LIBRARIES})

