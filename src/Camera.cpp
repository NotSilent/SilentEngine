#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const float aspectRatio) : m_view(glm::mat4{1.0f}),m_projection(glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f)) {
    m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -5.0f));
    m_view = glm::rotate(m_view, 10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::changeAspectRation(float aspectRatio) {
    m_projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}
