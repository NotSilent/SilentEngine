#pragma once

#include <vector>
#include <glad/glad.h>

#include "Shader.h"

class Mesh {
public:
    explicit Mesh(std::vector<float> &vertices);

    Mesh(const Mesh &other) = delete;

    Mesh &operator=(const Mesh &other) = delete;

    Mesh(Mesh &&other) noexcept;


    Mesh &operator=(Mesh &&other) noexcept;

    ~Mesh();

    void draw() const;

private:
    std::vector<float> m_vertices;

    GLuint m_vao;
    GLuint m_vbo;

    Shader m_shader;

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
};
