#include "Mesh.h"
#include "Vertex.h"

#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices) : m_manages(true), m_vao(0), m_vbo(0),
                                                                               m_ebo(0), m_vertices(vertices),
                                                                               m_indices(indices) {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    auto a = sizeof(Vertex);
    auto b = sizeof(float) * 3;

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_shader = Shader::getId("Unlit");
}

void Mesh::move(Mesh &other) {
    if (this != &other) {
        m_manages = true;
        other.m_manages = false;

        m_vao = other.m_vao;
        m_vbo = other.m_vbo;
        m_ebo = other.m_ebo;

        m_vertices = std::move(other.m_vertices);
        m_indices = std::move(other.m_indices);

        m_shader = other.m_shader;
    }
}

Mesh &Mesh::operator=(Mesh &&other) noexcept {
    move(other);

    return *this;
}

Mesh::Mesh(Mesh &&other) noexcept {
    move(other);
}

Mesh::~Mesh() {
    if (m_manages) {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteVertexArrays(1, &m_vao);
    }
}

void Mesh::draw(const glm::mat4& view, const glm::mat4& projection) const {
    glUseProgram(m_shader);

    glm::mat4 model = glm::mat4(1.0f);

    int modelLoc = glGetUniformLocation(m_shader, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(m_shader, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(m_shader, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}
