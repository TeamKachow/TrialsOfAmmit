#include "Window.h"

#include "../Common/InputManager.h"

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
	_window = glfwCreateWindow(width, height, name, NULL, NULL);

	// Error check if the _window fails to create
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW _window" << std::endl;

		glfwTerminate();
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, width, height);

	// Forces background of textures to blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void Hudson::Render::Window::SetWindow()
{
	// TODO: implement or remove
}

void Hudson::Render::Window::DestroyWindow()
{
	// TODO: implement or remove
}
