#pragma once
#include <glm/mat4x4.hpp>

class Camera {
public:
    Camera(float aspectRatio);
    Camera(const Camera& other) = delete;
    Camera& operator=(const Camera& other) = delete;
    Camera(Camera&& other) = delete;
    Camera&operator=(Camera&& other) = delete;

    inline glm::mat4 getView() const {
        return m_view;
    }

    inline glm::mat4 getProjection() const {
        return m_projection;
    }

    void changeAspectRation(float aspectRatio);
private:
    glm::mat4 m_view;
    glm::mat4 m_projection;
};
