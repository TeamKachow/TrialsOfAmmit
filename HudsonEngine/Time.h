#pragma once

#include <GLFW/glfw3.h>

#define FPS 1.0f / 60.0f

namespace Hudson::Util
{
	class Time
	{
	public:
		const float DeltaTime() const { return deltaTime; }
	private:
		Time();
		float CalculateDeltaTime();

		const float GetSeconds() const { return deltaTime; }
		const float GetMiliSeconds() const { return deltaTime * 1000.0f; }

	private:
		float currentTime = 0.0f;
		float deltaTime = 0.0f;
		float lastFrameTime = 0.0f;
	};
}

