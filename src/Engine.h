#pragma once

class GLFWwindow;

class Engine {
public:
    Engine(const char* name, int width, int height);
    ~Engine();

    Engine() = delete;
    Engine(const Engine& other) = delete;
    Engine& operator=(Engine& other) = delete;
    Engine(const Engine&& other) = delete;
    Engine& operator=(Engine&& other) = delete;

    void update();

private:
    GLFWwindow* m_window;

    void draw(float dt);
    void processInput(GLFWwindow *window);

    // Callbacks
    static void onWindowResize(GLFWwindow* window, int width, int height);
};