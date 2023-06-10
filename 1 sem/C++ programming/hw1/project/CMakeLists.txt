cmake_minimum_required(VERSION 3.0.0)
project(actor_films_lib)

set(CMAKE_CXX_STANDARD 20)


file(GLOB SOURCES ./src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES})

set(ACTOR_FILMS_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(ACTOR_FILMS_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
