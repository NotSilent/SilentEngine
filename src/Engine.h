#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "Mesh.h"

class Engine {
public:
    Engine(const char *name, int width, int height);

    ~Engine();

    void update();

private:
    GLFWwindow *m_window;

    std::vector<Mesh> m_meshes;

    void draw() const;

    void processInput(GLFWwindow *window);

    // Callbacks
    static void onWindowResize(GLFWwindow *window, int width, int height);
};