#include "Time.h"
Hudson::Util::Time::Time()
{

}

float Hudson::Util::Time::DeltaTime()
{
	static double deltaTime = 0.0f;
	double startTime = 0.0f;
	double currentTime = glfwGetTime();

	if (startTime == 0)
	{
		startTime = currentTime;
	}

	deltaTime = (currentTime - startTime) / 1000.0f;

	startTime = currentTime;

	static float accumulator = 0.0f;

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