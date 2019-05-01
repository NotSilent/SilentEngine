#pragma once

#include <vector>
#include "glad/glad.h"
#include <glm/mat4x4.hpp>

#include "Shader.h"

class Mesh {
public:
    explicit Mesh(std::vector<float> &vertices, std::vector<unsigned int> &indices);

    Mesh(const Mesh &other) = delete;

    Mesh &operator=(const Mesh &other) = delete;

    Mesh(Mesh &&other) noexcept;


    Mesh &operator=(Mesh &&other) noexcept;

    ~Mesh();

    void draw() const;

private:
    bool m_manages;

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    GLuint m_shader;

    glm::mat4 position;

    void move(Mesh &other);
};
