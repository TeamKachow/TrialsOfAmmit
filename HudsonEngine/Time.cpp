#include "Time.h"

Hudson::Util::Time::Time()
{
	 deltaTime = 0.0f;
	 startTime = 0.0f;
	 currentTime = 0.0f;
	 accumulator = 0.0f;
}

float Hudson::Util::Time::CalculateDeltaTime60FPS()
{
     deltaTime = 0.0f;
     startTime = 0.0f;
     currentTime = (float)glfwGetTime();

	if (startTime == 0)
	{
		startTime = currentTime;
	}

	deltaTime = (currentTime - startTime) / 1000.0f;

	startTime = currentTime;

	 accumulator = 0.0f;

	accumulator += deltaTime;

	if (accumulator >= FPS)
	{
		accumulator = accumulator - FPS;
	}
	else
	{
		return 0;
	}

	return deltaTime;
}