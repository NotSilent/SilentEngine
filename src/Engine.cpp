#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"

#include "Mesh.h"
#include "Vertex.h"
#include "WorldGenerator.h"

void APIENTRY
glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
              const void *userParam) {
    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "Source: API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Source: Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Source: Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Source: Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "Source: Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "Source: Other";
            break;
        default:
            std::cout << "Source: Unknown";
            break;
    }
    std::cout << std::endl;

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other";
            break;
        default:
            std::cout << "Type: Unknown";
            break;
    }
    std::cout << std::endl;

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: high\n";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: medium\n";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: low\n";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: notification\n";
            break;
        default:
            std::cout << "Severity: Unknown\n";
            break;
    }
    std::cout << std::endl;
}

Engine::Engine(const char *name, const int width, const int height) : m_camera(width / height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    if (!glfwInit())
        throw std::runtime_error("Couldn't initialize GLFW");

    m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create GLFW window");
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Couldn't initialize GLAD");
    }

    glViewport(0, 0, width, height);

    glCullFace(GL_FALSE);
    glFrontFace(GL_CCW);

    glfwSetFramebufferSizeCallback(m_window, onWindowResize);

    auto world = WorldGenerator::getWorld();

    m_meshes.emplace_back(Mesh{world.first, world.second});
}

Engine::~Engine() {
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

void Engine::update() {
    while (!glfwWindowShouldClose(m_window)) {
        processInput(m_window);
        draw();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Engine::draw() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &mesh : m_meshes) {
        mesh.draw(m_camera.getView(), m_camera.getProjection());
    }
}

void Engine::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Engine::onWindowResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    //m_camera.changeAspectRation(static_cast<float>(width) / height);
}