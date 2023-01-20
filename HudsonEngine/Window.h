#pragma once
#include "stdafx.h"


class InputManager;

namespace Hudson::Render {

	class Window {

	public:

		Window(int width, int height, const char* name);

		GLFWwindow* GetWindow() { return window; }
		void SetWindow();
		void DestroyWindow();

	private:
		GLFWwindow* window;
	};

}
