#pragma once
#include "stdafx.h"


namespace Hudson::Render {

	class Window {

	public:

		Window(int width, int height, const char* name);

		GLFWwindow* GetWindow() { return window; };
		glm::vec2 GetWindowExtent() { return windowExtent; };
		void SetWindow();
		void DestroyWindow();

	private:
		GLFWwindow* window;
		glm::vec2 windowExtent; // x = width, y = height
	};

}