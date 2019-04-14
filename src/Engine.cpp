#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Engine.h"

Engine::Engine(const char* name, const int width, const int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit())
        throw std::runtime_error("Couldn't initialize GLFW");

    m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Couldn't create GLFW window");
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Couldn't initialize GLAD");
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(m_window, onWindowResize);
}

Engine::~Engine() {
    if(m_window != nullptr){
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

void Engine::update() {
    while (!glfwWindowShouldClose(m_window))
    {
        processInput(m_window);
        draw(0.0f);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Engine::draw(float dt) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Engine::onWindowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}