#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Render {

	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top, float zNear, float zFar);

		void ViewMatrixCalculation();

		const glm::vec3& GetPosition() const { return _position; }
		void SetPosition(glm::vec3 position) { _position = position; ViewMatrixCalculation(); }

		const glm::mat4& GetProjectionMatrix() const { return _projection; }
		const glm::mat4& GetViewMatrix() const { return _view; }
		const glm::mat4& GetViewProjectionMatrix() const { return _viewProjection; }
		const glm::mat4& GetInverseViewProjectionMatrix() { return glm::inverse(_viewProjection); }
	private:
		glm::vec3 _position = { 200.0f, 200.0f, 0.0f };

		glm::mat4 _projection;
		glm::mat4 _view;
		glm::mat4 _viewProjection;
	};
}

