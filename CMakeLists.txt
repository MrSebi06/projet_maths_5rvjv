cmake_minimum_required(VERSION 4.0)
project(projet_maths_5rvjv)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

include_directories(include)

add_executable(projet_maths_5rvjv main.cpp
        src/glad.c
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
        src/Vector/Vector2.cpp
        src/Particles/Particle.cpp
        src/Physics/PhysicsSystem.cpp
        src/Particles/ParticleSystem.cpp
        include/Particles/ParticleSystem.h
        include/Engine.h
        src/Particles/ParticleEmitter.cpp
        include/Particles/ParticleEmitter.h
        include/Random.h
        include/Particles/Emitters/SparkleEmitter.h
        include/Physics/Rigidbody.h
        src/Physics/Rigidbody.cpp
        include/Physics/CollisionShape.h
        src/Mesh/MeshRenderer.cpp
        include/Mesh/MeshRenderer.h
        src/GameObject.cpp
        include/GameObject.h
        include/Physics/CollisionDetection.h
        include/imgui-1.92.5/imgui.h
        include/imgui-1.92.5/backends/imgui_impl_opengl3.h
        include/imgui-1.92.5/backends/imgui_impl_glfw.h
        include/imgui-1.92.5/backends/imgui_impl_opengl3.cpp
        include/imgui-1.92.5/backends/imgui_impl_glfw.cpp
        include/imgui-1.92.5/imgui.cpp
        include/imgui-1.92.5/imgui_draw.cpp
        include/imgui-1.92.5/imgui_tables.cpp
        include/imgui-1.92.5/imgui_widgets.cpp
        include/imgui-1.92.5/imgui_demo.cpp
        src/Transform.cpp
        include/Transform.h
        include/Mesh/Polygon/Square.h
        src/Physics/CollisionShapes/Circle.cpp
        src/Physics/CollisionShapes/Polygon.cpp
        src/Physics/CollisionShapes/Box.cpp
        include/input.h
        include/Mesh/Polygon/Rect.h
        include/Physics/LiquidBody.h
        src/Physics/LiquidBody.cpp
        include/Globals.h
        src/Emitter.cpp
        include/Emitter.h
        src/Physics/PhysicsEmitter.cpp
        include/Physics/PhysicsEmitter.h
)

target_link_libraries(projet_maths_5rvjv ${OPENGL_LIBRARIES} glfw)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})