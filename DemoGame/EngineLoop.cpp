
// Note needs refactoring
#include <iostream>

#include <Common/Engine.h>
#include <Common/ResourceManager.h>

void Init() {

    /*
    Hudson::Common::ResourceManager::Setup();

    auto resManager = Hudson::Common::ResourceManager::GetInstance();

    resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

    Hudson::Common::ResourceManager::Destroy();
    */

    Hudson::Common::Engine* engine = new Hudson::Common::Engine([](Hudson::Common::Engine* engine)
        {
            engine->GetSceneManager()->LoadScene("menu.scene");
            std::cout << "DemoGame: engine post-setup hook!\n";
        });

    engine->Setup();

    engine->Run();

    engine->Cleanup();

    delete engine;
}

int main() {
    Init();
}