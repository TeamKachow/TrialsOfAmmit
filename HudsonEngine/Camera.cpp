#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top) 
{
	m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_view = glm::mat4(1.0f);
	m_viewProjection = m_projection * m_view;
}

void Camera::ViewMatrixCalculation()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position);
	m_view = glm::inverse(transform);
	m_viewProjection = m_projection * m_view;
}