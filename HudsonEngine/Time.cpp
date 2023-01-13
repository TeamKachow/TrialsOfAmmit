#include "Time.h"

Hudson::Util::Time::Time()
{
	currentTime = 0.0f;
	deltaTime = 0.0f;
	lastFrameTime = 0.0f;
}

float Hudson::Util::Time::CalculateDeltaTime()
{
	currentTime = (float)glfwGetTime();

	deltaTime = (currentTime - lastFrameTime) / 1000.0f;

	if (lastFrameTime == 0)
	{
		lastFrameTime = currentTime;
	}

	if (deltaTime < FPS)
	{
		return;
	}

	return deltaTime;
}