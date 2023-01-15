 
// Note needs refactoring
#include <iostream>
#include "HudsonEngine/Common/ResourceManager.h"

void Init() {
	Hudson::Common::ResourceManager::Setup();

	auto resManager = Hudson::Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

	Hudson::Common::ResourceManager::Destroy();
}

int main() {
	//Init();
}