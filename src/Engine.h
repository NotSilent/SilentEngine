#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include "Mesh.h"
#include "Camera.h"

class Engine {
public:
    Engine(const char *name, int width, int height);
    Engine(const Engine& other) = delete;
    Engine& operator=(const Engine& other) = delete;
    Engine(Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;

    ~Engine();

    void update();

private:
    GLFWwindow *m_window;

    std::vector<Mesh> m_meshes;

    Camera m_camera;

    void draw() const;

    void processInput(GLFWwindow *window);

    // Callbacks
    static void onWindowResize(GLFWwindow *window, int width, int height);
};