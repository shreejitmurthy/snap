cmake_minimum_required(VERSION 3.27)
project(snap C)

set(CMAKE_C_STANDARD 99)

include_directories(vendor)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/cglm)

set(ENGINE_SOURCES src/gfx.c src/shader.c)
add_library(libsnap STATIC ${ENGINE_SOURCES} vendor/glad/glad.c)

find_package(OpenGL REQUIRED)
target_include_directories(libsnap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(libsnap OpenGL::GL cglm SDL3::SDL3)