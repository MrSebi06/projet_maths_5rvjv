cmake_minimum_required(VERSION 4.0)
project(projet_maths_5rvjv)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories(include)

add_executable(projet_maths_5rvjv main.cpp src/glad.c
        src/Mesh.cpp
        include/Mesh.h
        src/init.cpp
        include/init.h)

target_link_libraries(projet_maths_5rvjv ${OPENGL_LIBRARIES} glfw)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})