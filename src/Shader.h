#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <fstream>

class Shader {
    using Shaders = std::unordered_map<std::string, Shader>;

public:
    explicit Shader(const std::string &name);

    Shader(const Shader &other) = delete;

    Shader &operator=(const Shader &other) = delete;

    Shader(Shader &&other) noexcept;

    Shader &operator=(Shader &&other) noexcept;

    ~Shader();

    static GLuint getId(const std::string &name);

    bool m_manages;

    GLuint m_id;

    static Shaders m_shaders;

    inline GLuint getId() const {
        return m_id;
    }

    std::string getSource(std::ifstream &stream, std::string &&name);

    void move(Shader &other);
};