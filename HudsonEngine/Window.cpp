#include "Window.h"

using namespace Hudson;

Render::Window::Window(int width, int height, const char* name) {

	glfwInit();
	// GLFW what version of OpenGL we are using - OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of defined pixels
	window = glfwCreateWindow(width, height, name, glfwGetPrimaryMonitor(), NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		glfwTerminate();
	}

}

void Hudson::Render::Window::SetWindow()
{
}

void Hudson::Render::Window::DestroyWindow()
{
}

void Hudson::Render::Window::ChangeContext()
{
	glfwMakeContextCurrent(this->window);
}
