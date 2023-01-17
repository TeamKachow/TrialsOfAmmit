 
// Note needs refactoring
#include <iostream>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Window.h"
#include "Camera.h"

using namespace Hudson;

Render::Window mainWindow(1280,720, "Hudson Engine");
Camera firstCamera(0.0f, 1600.0f, 900.0f, 0.0f);
Render::SpriteRenderer* Sprite1;
Common::ResourceManager* resManager;

void Init() {

	Common::ResourceManager::SetupInstance(); // Setups Instance
	resManager = Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));
	
	resManager->GetShader("spriteShader")->Use().SetInteger("image", 0);
	resManager->GetShader("spriteShader")->SetMatrix4("projection", firstCamera.GetProjectionMatrix());

	Sprite1 = new Render::SpriteRenderer(resManager->GetShader("spriteShader"));
	Sprite1->SetSize(glm::vec2(128.0f, 128.0f));
	Sprite1->SetGridSize(glm::vec2(3, 4));
	//Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

	// load textures
	resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");

}

void Destroy() {
	//Hudson::Common::ResourceManager::DestroyInstance();
}

void randomisePosition() {

	int x = Sprite1->GetGridPos().x;
	glm::vec2 spriteGridSize = Sprite1->GetGridSize();

	if (x >= spriteGridSize.x - 1) {
		x = 0;
	}
	else {
		x += 1;
	}

	//int x = rand() % 3; // 0 - 2
	//int y = rand() % 4; // 0 - 3
	Sprite1->SetGridPos(glm::vec2(x, 0));
	
}

int main() {

	Init();

	int x = 0;

	while (!glfwWindowShouldClose(mainWindow.GetWindow()))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (x == 30) {
			randomisePosition();
			x = 0;
		}

		Sprite1->DrawSprite(resManager->GetTexture("Mummy"),glm::vec2(200.0f, 200.0f));

		//GameObject->Update()

		//Sprite1.SetShaderColor()

		++x;

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(mainWindow.GetWindow());
		// Take care of all GLFW events
		glfwPollEvents();
	}
}