#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>

class Shader {
public:
    Shader();

    Shader(const std::string &&name, const std::string &vertexSource, const std::string &fragmentSource);

    Shader(const Shader &other) = delete;

    Shader &operator=(const Shader &other) = delete;

    Shader(Shader &&other) noexcept;

    Shader &operator=(Shader &&other) noexcept;

    ~Shader();

    inline GLuint getId() const {
        return m_id;
    }

private:
    GLuint m_id;
    std::string m_name;

    static std::unordered_map<std::string, Shader> shaders;
};