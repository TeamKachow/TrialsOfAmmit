#include "Camera.h"

using namespace Hudson::Render;

Camera::Camera(float left, float right, float bottom, float top, float zNear, float zFar) : _projection(glm::ortho(left, right, bottom, top, zNear, zFar)), _view(1.0f)
{
	_viewProjection = _projection * _view;
}

void Camera::ViewMatrixCalculation()
{
	_view = glm::inverse(glm::translate(glm::mat4(1.0f), _position));
	_viewProjection = _projection * _view;
}