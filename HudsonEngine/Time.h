#pragma once

#include <GLFW/glfw3.h>

#define FPS 1.0f / 60.0f

namespace Hudson::Util
{
	class Time
	{
	public:
		Time();
		float CalculateDeltaTime60FPS();
	private:
		float deltaTime = 0.0f;
		float startTime = 0.0f;
		float currentTime = 0.0f;
		float accumulator = 0.0f;
	};
}


