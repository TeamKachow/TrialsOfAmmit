 
// Note needs refactoring
#include <iostream>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Window.h"
#include "Camera.h"

using namespace Hudson;

Render::Window mainWindow(1280,720, "Hudson Engine");
Camera firstCamera(0.0f, 800.0f, 800.0f, 0.0f);
Render::SpriteRenderer* Sprite1;
Common::ResourceManager* resManager;

void Init() {

	Common::ResourceManager::SetupInstance(); // Setups Instance
	resManager = Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));
	
	resManager->GetShader("spriteShader")->Use().SetInteger("image", 0);
	resManager->GetShader("spriteShader")->SetMatrix4("projection", firstCamera.GetProjectionMatrix());

	Sprite1 = new Render::SpriteRenderer(resManager->GetShader("spriteShader"));
	Sprite1->SetSize(glm::vec2(500.0f, 500.0f));
	//Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

	// load textures
	resManager->LoadTexture("textures/images.jpg", false, "Doc");

}

void Destroy() {
	//Hudson::Common::ResourceManager::DestroyInstance();
}

int main() {

	Init();

	while (!glfwWindowShouldClose(mainWindow.GetWindow()))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Sprite1->DrawSprite(resManager->GetTexture("Doc"),glm::vec2(200.0f, 200.0f));

		//GameObject->Update()

		//Sprite1.SetShaderColor()

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(mainWindow.GetWindow());
		// Take care of all GLFW events
		glfwPollEvents();
	}
}