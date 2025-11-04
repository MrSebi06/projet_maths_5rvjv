#ifndef PROJET_MATHS_MESH_H
#define PROJET_MATHS_MESH_H
#include "glad/glad.h"


struct Mesh {
    GLuint VAO{}, VBO{}, EBO{};
    GLsizei index_count{};

    ~Mesh() { cleanup(); }

    void draw() const;

    void cleanup();
};

Mesh create_mesh(const float *vertices, GLsizeiptr vertices_size,
                 const unsigned int *indices, GLsizeiptr indices_size);

#endif //PROJET_MATHS_MESH_H
