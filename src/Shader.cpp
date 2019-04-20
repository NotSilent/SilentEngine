#include "Shader.h"
#include <iostream>
#include <sstream>

Shader::Shaders Shader::m_shaders = Shader::Shaders{};

Shader::Shader(const std::string &name) : m_manages(true) {
    const auto vertex = glCreateShader(GL_VERTEX_SHADER);
    const auto fragment = glCreateShader(GL_FRAGMENT_SHADER);

    std::ifstream stream;
    auto a = getSource(stream, name + ".vert");
    auto rawSource = a.c_str();
    glShaderSource(vertex, 1, &rawSource, nullptr);
    glCompileShader(vertex);

    a = getSource(stream, name + ".frag");
    rawSource = a.c_str();
    glShaderSource(fragment, 1, &rawSource, nullptr);
    glCompileShader(fragment);

    m_id = glCreateProgram();

    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);

    glLinkProgram(m_id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::move(Shader &other) {
    if (this != &other) {
        m_manages = true;
        other.m_manages = false;

        m_id = other.m_id;
    }
}

Shader &Shader::operator=(Shader &&other) noexcept {
    move(other);

    return *this;
}

Shader::Shader(Shader &&other) noexcept {
    move(other);
}

Shader::~Shader() {
    if (m_manages) {
        glDeleteProgram(m_id);
    }
}

GLuint Shader::getId(const std::string &name) {
    const auto shaderIterator = m_shaders.find(name);

    if (shaderIterator == m_shaders.end()) {
        Shader shader{name};

        GLuint id = shader.m_id;

        auto a = m_shaders.emplace(name, std::move(shader));

        return id;
    }

    return shaderIterator->second.m_id;
}

std::string Shader::getSource(std::ifstream &stream, std::string &&name) {
    stream.open("../shaders/" + name);

    if (!stream.is_open()) {
        throw std::runtime_error("Couldn't open shader file: " + name);
    }

    std::stringstream source;
    source << stream.rdbuf();

    stream.close();

    std::string raw = source.str();
    return raw;
}
