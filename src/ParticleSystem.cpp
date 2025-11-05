//
// Created by mihne on 05/11/2025.
//

#include "ParticleSystem.h"

void ParticleSystem::setup_geometry() {
    constexpr float radius = 0.1f;
    constexpr int segments = 18;
    constexpr double angle = 360.0 / segments;

    std::vector<Vector2> vertices;
    for (unsigned int i = 0; i < segments; i++) {
        const double currentAngle = angle * i;
        double x = radius * cos(deg2rad(currentAngle));
        double y = radius * sin(deg2rad(currentAngle));

        vertices.emplace_back(x, y);
    }

    std::vector<GLuint> indices;
    for (int i = 1; i < segments - 1; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indexCount = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void ParticleSystem::setup_instance_buffer() {
    glBindVertexArray(VAO);

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 MAX_PARTICLES * sizeof(ParticleInstance),
                 nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstance), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleInstance),
                          reinterpret_cast<void *>(offsetof(ParticleInstance, color)));
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    glBindVertexArray(0);
}


void ParticleSystem::update(const float dt) {
    for (auto &p: particles) {
        p.integrate(dt);
    }
}

void ParticleSystem::draw() const {
    instanceData.clear();
    instanceData.reserve(particles.size());

    for (const auto &p: particles) {
        instanceData.push_back({p.position, p.color});
    }

    if (instanceData.empty()) return;

    // Upload instance data
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, instanceData.size() * sizeof(ParticleInstance),
                    instanceData.data());

    // Draw all particles in ONE call
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr,
                            instanceData.size());
}

void ParticleSystem::emit() {
    if (particles.size() < MAX_PARTICLES) {
        particles.emplace_back(Vector2(0.0, 0.0), Vector3(1.0, 1.0, 0.0));
    }
}

void ParticleSystem::add_force(const Vector2 &force) {
    for (auto &p: particles) {
        p.addForce(force);
    }
}
