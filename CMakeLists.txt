cmake_minimum_required(VERSION 4.0)
project(projet_maths_5rvjv)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

include_directories(include)

add_executable(projet_maths_5rvjv main.cpp src/glad.c
        src/Mesh/Mesh.cpp
        include/Mesh/Mesh.h
        src/init.cpp
        include/init.h
        src/Mesh/Circle/Circle.cpp
        include/Mesh/Circle/Circle.h
        include/helpers.h
        src/helpers.cpp
        include/Vector/Vector3.h
        include/Vector/Vector2.h
        src/Vector/Vector3.cpp
        src/Vector/Vector2.cpp)

target_link_libraries(projet_maths_5rvjv ${OPENGL_LIBRARIES} glfw)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})