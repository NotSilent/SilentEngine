#pragma once

#include <vector>
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "Shader.h"
#include "Vertex.h"

class Mesh {
public:
    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);

    Mesh(const Mesh &other) = delete;

    Mesh &operator=(const Mesh &other) = delete;

    Mesh(Mesh &&other) noexcept;


    Mesh &operator=(Mesh &&other) noexcept;

    ~Mesh();

    void draw(const glm::mat4& view, const glm::mat4& projection) const;

private:
    bool m_manages;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    GLuint m_shader;

    void move(Mesh &other);
};
