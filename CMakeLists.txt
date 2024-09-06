cmake_minimum_required(VERSION 3.27)
project(snap_examples C)

add_subdirectory(snap)

file(GLOB_RECURSE SOURCES "examples/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} libsnap)