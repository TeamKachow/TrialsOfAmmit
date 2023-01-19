
// Note needs refactoring
#include <iostream>

#include <Common/Engine.h>
#include <Common/ResourceManager.h>
#include <SpriteComponent.h>
#include <PhysicsComponent.h>

#include "DemoBehaviour.h"
#include "GameObject.h"
#include "Scene.h"

Hudson::Common::Engine* engine;
Hudson::Render::SpriteComponent* Sprite1;
Hudson::Physics::PhysicsComponent* Physics1;
// TODO: this *needs* to move to Hudson ASAP
Hudson::Common::ResourceManager* resManager;

void Init() 
{
    Hudson::Common::ResourceManager::SetupInstance(); // Set up single resource manager (TODO: decide per-scene/per-game)
    resManager = Hudson::Common::ResourceManager::GetInstance();

    engine = new Hudson::Common::Engine([](Hudson::Common::Engine* engine) {});

    engine->Setup();
}

void GameSetup()
{
    Sprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"));
    Sprite1->SetSize(glm::vec2(128.0f, 128.0f));
    Sprite1->SetGridSize(glm::vec2(3, 4));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Physics1 = new Hudson::Physics::PhysicsComponent();
    Physics1->SetMass(1.0f);
    Physics1->SetForce(glm::vec2(10.0, 0));
    Physics1->SetAcceleration(glm::vec2(100, 0));
    Physics1->SetVelocity(glm::vec2(100, 0));
#
    // Load initial scene from file 
    // TODO: Hudson::World::Scene* startScene = engine->GetSceneManager()->LoadScene("menu.scene");
    Hudson::World::Scene* startScene = new Hudson::World::Scene();
    engine->GetSceneManager()->AddScene(startScene);

    Hudson::Entity::GameObject* blah = new Hudson::Entity::GameObject();
    blah->AddComponent(Sprite1);
    blah->AddComponent(new DemoBehaviour(Sprite1));
    blah->AddComponent(Physics1);
    startScene->AddObject(blah);

    std::cout << "DemoGame: engine has been set up!\n";
}

int main() {
    Init();

    // Set up game scene/resources
    GameSetup();

    // Run engine loop until it is shut down
    engine->Run();

    // Clean up
    engine->Cleanup();
    delete engine;
}
