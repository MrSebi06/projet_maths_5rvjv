#include "Mesh/Mesh.h"

#include <stdexcept>

void Mesh::setup_geometry(const Vector2 *vertices, const GLsizeiptr vertices_size,
                          const GLuint *indices, const GLsizeiptr indices_size) {
    if (!vertices || !indices || vertices_size == 0 || indices_size == 0) {
        throw std::invalid_argument("Invalid mesh data");
    }

    index_count = static_cast<GLsizei>(indices_size / sizeof(unsigned int));

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::bind() const {
    glBindVertexArray(VAO);
}

void Mesh::unbind() const {
    glBindVertexArray(0);
}


void Mesh::cleanup() {
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
}
