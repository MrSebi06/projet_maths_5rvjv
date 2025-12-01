#ifndef PROJET_MATHS_MESH_H
#define PROJET_MATHS_MESH_H

#include "glad/glad.h"
#include "Vector/Vector2.h"


struct Mesh {
    GLuint VAO{}, VBO{}, EBO{};
    GLsizei index_count{};

    ~Mesh() { cleanup(); }

    void cleanup();
    void setup_geometry(const Vector2 *vertices, GLsizeiptr vertices_size,
                        const unsigned int *indices, GLsizeiptr indices_size);
    void bind() const;
    void unbind() const;

public:
    GLsizei get_index_count() const { return index_count; }
};


#endif //PROJET_MATHS_MESH_H
