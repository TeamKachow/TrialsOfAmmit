 
// Note needs refactoring
#include <iostream>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Window.h"
#include "Camera.h"

using namespace Hudson;

Render::Window mainWindow(1920,1080, "Hudson Engine");
Camera firstCamera(-1.0f, 1.0f, -1.0f, 1.0f);
Render::SpriteRenderer* Renderer;

void Init() {

	mainWindow.ChangeContext();

	//Common::ResourceManager::SetupInstance(); // Setups Instance
	//auto resManager = Common::ResourceManager::GetInstance();
	//resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

	//resManager->GetShader("spriteShader").Use().SetInteger("image", 0);
	//resManager->GetShader("spriteShader").SetMatrix4("projection", firstCamera.GetProjectionMatrix());

	// load textures
	//resManager->LoadTexture("", true, "face");

}

void Destroy() {
	//Hudson::Common::ResourceManager::DestroyInstance();
}

int main() {
	Init();

	while (!glfwWindowShouldClose(mainWindow.GetWindow()))
	{
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(mainWindow.GetWindow());
		// Take care of all GLFW events
		glfwPollEvents();
	}
}