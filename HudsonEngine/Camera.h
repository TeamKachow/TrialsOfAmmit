#pragma once

#include<glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(float left, float right, float bottom, float top);

	void ViewMatrixCalculation();

	const glm::vec3& GetPosition() const { return m_position; }
	void SetPosition(const glm::vec3& position) { m_position = position; ViewMatrixCalculation(); }

	const glm::mat4& GetProjectionMatrix() const { return m_projection; }
	const glm::mat4& GetViewMatrix() const { return m_view; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjection; }
private:
	glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };

	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 m_viewProjection;
};

