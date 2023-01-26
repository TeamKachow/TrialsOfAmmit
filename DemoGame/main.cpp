
// Note needs refactoring
#include <iostream>

#include <../Common/Engine.h>
#include <../Common/ResourceManager.h>
#include <../Render/SpriteComponent.h>
#include <../Physics/PhysicsComponent.h>
#include <../Physics/ColliderComponent.h>
#include <../Editor/Editor.h>
#include <../Entity/GameObject.h>
#include <../World/Scene.h>
#include <../Common/InputManager.h>

#include "DemoBehaviour.h"

Hudson::Common::Engine* engine;
Hudson::Editor::Editor* editor;
Hudson::Render::SpriteComponent* Sprite1;
Hudson::Render::SpriteComponent* Sprite2;
Hudson::Physics::PhysicsComponent* Physics1;
Hudson::Physics::PhysicsComponent* Physics2;
Hudson::Physics::ColliderComponent* Collider1;
Hudson::Physics::ColliderComponent* Collider2;
// TODO: this *needs* to move to Hudson ASAP
Hudson::Common::ResourceManager* resManager;
void Init() 
{
    Hudson::Common::ResourceManager::SetupInstance(); // Set up single resource manager (TODO: decide per-scene/per-game)
    resManager = Hudson::Common::ResourceManager::GetInstance();

    engine = new Hudson::Common::Engine();

    editor = new Hudson::Editor::Editor(engine);

    engine->Setup();
}

void GameSetup()
{
    Sprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"));
    Sprite1->SetSize(glm::vec2(64.0f, 64.0f));
    Sprite1->SetGridSize(glm::vec2(3, 4));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Sprite2 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"));
    Sprite2->SetSize(glm::vec2(64.0f, 64.0f));
    Sprite2->SetGridSize(glm::vec2(3, 4));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Physics1 = new Hudson::Physics::PhysicsComponent();
    Physics1->SetMass(1.0f);
    Physics1->SetForce(glm::vec2(10.0, 0));
    Physics1->SetAcceleration(glm::vec2(100, 0), true);
    Physics1->SetVelocity(glm::vec2(100, 0));

    Physics2 = new Hudson::Physics::PhysicsComponent();
    Physics2->SetMass(1.0f);
    Physics2->SetForce(glm::vec2(-10.0, 0));
    Physics2->SetAcceleration(glm::vec2(-100, 0), true);
    Physics2->SetVelocity(glm::vec2(-100, 0));

    Collider1 = new Hudson::Physics::ColliderComponent();
    Collider2 = new Hudson::Physics::ColliderComponent();

    // Load initial scene from file 
    // TODO: Hudson::World::Scene* startScene = engine->GetSceneManager()->LoadScene("menu.scene");
    Hudson::World::Scene* startScene = new Hudson::World::Scene();
    engine->GetSceneManager()->AddScene(startScene);

    Hudson::Entity::GameObject* blah = new Hudson::Entity::GameObject();
    blah->AddComponent(Sprite1);
    blah->AddComponent(new DemoBehaviour(Sprite1));
    blah->AddComponent(Physics1);
    blah->AddComponent(Collider1);
    startScene->AddObject(blah);

    blah->GetTransform().pos.x = 200.0f;

    Hudson::Entity::GameObject* blah2 = new Hudson::Entity::GameObject();
    blah2->AddComponent(Sprite2);
    blah2->AddComponent(new DemoBehaviour(Sprite2));
    blah2->AddComponent(Physics2);
    blah2->AddComponent(Collider2);
    startScene->AddObject(blah2);

    blah2->GetTransform().pos.x = 1400.0f;

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
