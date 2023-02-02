#include "Camera.h"

using namespace Hudson::Render;

Camera::Camera(float left, float right, float bottom, float top) 
{
	_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	_view = glm::mat4(1.0f);
	_viewProjection = _projection * _view;
}

void Camera::ViewMatrixCalculation()
{
	_view = glm::translate(glm::mat4(1.0f), _position);
	_viewProjection = _projection * _view;
}