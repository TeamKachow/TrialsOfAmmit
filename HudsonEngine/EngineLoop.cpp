 
// Note needs refactoring
#include <iostream>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Window.h"
#include "Camera.h"
#include "PhysicsManager.h"
using namespace Hudson;

Render::Window mainWindow(1280,720, "Hudson Engine");
Camera firstCamera(0.0f, 800.0f, 800.0f, 0.0f);
Render::SpriteRenderer* Sprite1;
Common::ResourceManager* resManager;
Physics::PhysicsManager* phyManager;

void Init() {

	Common::ResourceManager::SetupInstance(); // Setups Instance
	resManager = Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));
	
	resManager->GetShader("spriteShader")->Use().SetInteger("image", 0);
	resManager->GetShader("spriteShader")->SetMatrix4("projection", firstCamera.GetProjectionMatrix());

	Sprite1 = new Render::SpriteRenderer(resManager->GetShader("spriteShader"));
	Sprite1->SetSize(glm::vec2(200.0f, 200.0f));
	//Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

	// load textures
	resManager->LoadTexture("textures/images.jpg", false, "Doc");

}

void Draw()
{
	Sprite1->DrawSprite(resManager->GetTexture("Doc"), glm::vec2(200.0f, 200.0f));

	//Sprite1.SetShaderColor()
}

void Destroy() {
	//Hudson::Common::ResourceManager::DestroyInstance();
}


int main() {

	Init();

	static double limitFPS = 1.0f / 60.0f;
	double lastTime = glfwGetTime();
	double timer = lastTime;
	double deltaTime = 0;
	double nowTime = 0;
	int frames = 0; 
    int updates = 0;

	while (!glfwWindowShouldClose(mainWindow.GetWindow()))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		phyManager->UpdatePhysics();


		//// Measure time
		//nowTime = glfwGetTime();
		//deltaTime += ((nowTime - lastTime) / limitFPS);
		//lastTime = nowTime;

		//// Only updates at 60 frames / s - Physics and any 60FPS locked stuff here
		//while (deltaTime >= 1.0f)
		//{
		//	phyManager->UpdatePhysics(updates);
		//	updates++;
		//	deltaTime--;
		//}

		//// Renders at maximum possible frames - Render Here
		Draw();
		//frames++;
		//
		//// Reset after one second
		//if (glfwGetTime() - timer > 1.0f) {
		//	timer++;
		//	std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
		//	updates = 0, frames = 0;
		//}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(mainWindow.GetWindow());
		// Take care of all GLFW events
		glfwPollEvents();
	}

	//phyManager->Cleanup();
}