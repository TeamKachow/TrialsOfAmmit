 
// Note needs refactoring
#include <iostream>

#include "HudsonEngine/Common/Engine.h"
#include "HudsonEngine/Common/ResourceManager.h"

void Init() {

	/*
	Hudson::Common::ResourceManager::Setup();

	auto resManager = Hudson::Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

	Hudson::Common::ResourceManager::Destroy();
	*/
	auto engine = new Hudson::Common::Engine([] (Hudson::Common::Engine* engine)
	{
		std::cout << "DemoGame: engine post-setup hook!\n";
	});

	engine->Run();

	engine->Cleanup();

	delete engine;
}

int main() {
	Init();
}