#pragma once

#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>


namespace Hudson::Render {

	class Window {

	public:

		Window(int width, int height, const char* name);

		GLFWwindow* GetWindow() { return window; };
		void SetWindow();
		void DestroyWindow();

	private:
		GLFWwindow* window;
	};

}