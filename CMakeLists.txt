cmake_minimum_required(VERSION 4.0)
project(projet_maths)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(include)

add_executable(projet_maths main.cpp src/glad.c
        src/Mesh.cpp
        src/Mesh.h
        src/init.cpp
        include/init.h)

target_link_libraries(projet_maths ${OPENGL_LIBRARIES} glfw)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})