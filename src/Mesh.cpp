#include "Mesh.h"

Mesh::Mesh(std::vector<float> &vertices) : m_vao(0), m_vbo(0), m_vertices(vertices) {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, m_vertices.size() / 3, GL_FLOAT, GL_FALSE, m_vertices.size() * sizeof(float) / 3, nullptr);
    glEnableVertexAttribArray(0);

    // Unbind (not necessary)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_shader = Shader{"", vertexShaderSource, fragmentShaderSource};
}

Mesh &Mesh::operator=(Mesh &&other) noexcept {
    if (this != &other) {
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_vertices = std::move(other.m_vertices);
        m_shader = std::move(other.m_shader);
    }

    return *this;
}

Mesh::Mesh(Mesh &&other) noexcept {
    if (this != &other) {
        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_vertices = std::move(other.m_vertices);
        m_shader = std::move(other.m_shader);
    }
}

void Mesh::draw() const {
    glUseProgram(m_shader.getId());
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

Mesh::~Mesh() {
    //glDeleteBuffers(1, &m_vbo);
    //glDeleteVertexArrays(1, &m_vao);
}
