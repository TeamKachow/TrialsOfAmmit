#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top) 
{
	m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_view = glm::mat4(1.0f);
	m_viewProjection = m_projection * m_view;
}

void Camera::ViewMatrixCalculation()
{
	m_view = glm::translate(glm::mat4(1.0f), m_position);
	m_viewProjection = m_projection * m_view;
}