#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#define FPS 1.0f / 30.0f

namespace Hudson::Util
{
	class Time
	{
	public:
		Time();
		float DeltaTime();
	};
}


