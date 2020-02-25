#include "mgpch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace MyGE {

    OrthographicCamera::OrthographicCamera(float Left, float Right, float Bottom, float Top)
        : m_ProjectionMatrix(glm::ortho(Left, Right, Bottom, Top, /* Near */ -1.0f, /* Far */ 1.0f)), m_ViewMatrix(1.0f)
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 Transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        m_ViewMatrix = glm::inverse(Transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}