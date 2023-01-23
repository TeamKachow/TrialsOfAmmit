#pragma once
#include "../Util/stdafx.h"


class InputManager;

namespace Hudson::Render {

	class Window {

	public:

		Window(int width, int height, const char* name);
		
		GLFWwindow* GetWindow() { return _window; };
		void SetWindow();
		void DestroyWindow();

	private:
		GLFWwindow* _window;
	};

}
