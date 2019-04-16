#include "Shader.h"
#include <iostream>

Shader::Shader() : m_id(0), m_name("") {

}

Shader::Shader(const std::string &&name, const std::string &vertexSource, const std::string &fragmentSource) {
    const auto vertex = glCreateShader(GL_VERTEX_SHADER);
    const auto fragment = glCreateShader(GL_FRAGMENT_SHADER);

    auto rawSource = vertexSource.c_str();
    glShaderSource(vertex, 1, &rawSource, nullptr);
    glCompileShader(vertex);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    rawSource = fragmentSource.c_str();
    glShaderSource(fragment, 1, &rawSource, nullptr);
    glCompileShader(fragment);

    // check for shader compile errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    m_id = glCreateProgram();

    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    //glDeleteProgram(m_id);
}

Shader &Shader::operator=(Shader &&other) noexcept {
    if (this != &other) {
        m_id = other.m_id;
        m_name = std::move(other.m_name);
    }

    return *this;
}

Shader::Shader(Shader &&other) noexcept {
    if (this != &other) {
        m_id = other.m_id;
        m_name = std::move(other.m_name);
    }
}
