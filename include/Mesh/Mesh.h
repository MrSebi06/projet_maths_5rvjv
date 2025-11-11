#ifndef PROJET_MATHS_MESH_H
#define PROJET_MATHS_MESH_H

#include "glad/glad.h"
#include "Vector/Vector2.h"


struct Mesh {
    GLuint VAO{}, VBO{}, EBO{};
    GLuint shader_program{};
    GLint modelLoc{};
    GLsizei index_count{};

    ~Mesh() { cleanup(); }

    void draw(const Vector2 *position) const;

    void cleanup();

    void register_vertices(const Vector2 *vertices, GLsizeiptr vertices_size,
                           const unsigned int *indices, GLsizeiptr indices_size);

    void assign_shader(const GLuint shader_program_) {
        shader_program = shader_program_;
        modelLoc = glGetUniformLocation(shader_program, "position");
    }
};


#endif //PROJET_MATHS_MESH_H
