#include <iostream>

#include <Hudson.h>

#include "DemoBehaviour.h"
#include "Player.h"

Hudson::Common::Engine* engine;
Hudson::Editor::ComponentRegistry* registry;

#ifdef _DEBUG
#define ENABLE_EDITOR
#endif

#ifdef ENABLE_EDITOR
#pragma message("Creating an editor build")
#endif

#ifdef ENABLE_EDITOR
Hudson::Editor::Editor* editor;
#endif

Hudson::Render::Camera* _defaultCamera = new Hudson::Render::Camera(0.0f, 1600.0f, 900.0f, 0.0f);

Hudson::Render::TextComponent* Text1;
Hudson::Render::TextComponent* Text2;

Hudson::Render::SpriteComponent* Sprite1;
Hudson::Render::SpriteComponent* Sprite2;
Hudson::Physics::PhysicsComponent* Physics1;
Hudson::Physics::PhysicsComponent* Physics2;
Hudson::Physics::ColliderComponent* Collider1;
Hudson::Physics::ColliderComponent* Collider2;

//Player 
Hudson::Render::SpriteComponent* playerSprite;
Hudson::Physics::PhysicsComponent* playerPhysics;
Hudson::Physics::ColliderComponent* playerCollider;




// TODO: this *needs* to move to Hudson ASAP
Hudson::Common::ResourceManager* resManager;

void InitRegistry()
{
    registry = new Hudson::Editor::ComponentRegistry();
    registry->RegisterEngineComponents();

    registry->Register<DemoBehaviour>("Demo Behaviour");
}

void Init() 
{
    Hudson::Common::ResourceManager::SetupInstance(); // Set up single resource manager (TODO: decide per-scene/per-game)
    resManager = Hudson::Common::ResourceManager::GetInstance();

    engine = new Hudson::Common::Engine();

#ifdef ENABLE_EDITOR
    InitRegistry();
    editor = new Hudson::Editor::Editor(engine, registry);
#endif

    engine->Setup();
}

void GameSetup()
{
    resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));
    // Shader needs to be Use() to pass values over
    resManager->GetShader("spriteShader")->Use().SetMatrix4("projection", _defaultCamera->GetProjectionMatrix());

    resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");

    playerSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
    playerSprite->SetSize(glm::vec2(64.0f, 64.0f));
    playerSprite->SetGridSize(glm::vec2(3, 4));
    playerSprite->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));

    playerPhysics = new Hudson::Physics::PhysicsComponent();
    playerPhysics->SetMass(1.0f);
    playerPhysics->SetForce(glm::vec2(0.0, 0));
    playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
    playerPhysics->SetVelocity(glm::vec2(0, 0));


    Sprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
    Sprite1->SetSize(glm::vec2(64.0f, 64.0f));
    Sprite1->SetGridSize(glm::vec2(3, 4));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Sprite2 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
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
    playerCollider = new Hudson::Physics::ColliderComponent();

    Text1 = new Hudson::Render::TextComponent("Fonts/arial.ttf", _defaultCamera->GetProjectionMatrix(), glm::vec2(20.0f, 20.0f));
    Text1->SetText("the quick brown fox jumps over the lazy dog");
    Text1->SetColor(glm::vec3(0.5, 0.8f, 0.2f));

    Text2 = new Hudson::Render::TextComponent("Fonts/arial.ttf", _defaultCamera->GetProjectionMatrix(), glm::vec2(20.0f, 20.0f));
    Text2->SetText("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
    Text2->SetColor(glm::vec3(0.5, 0.8f, 0.2f));

    // Load initial scene from file 
    // TODO: Hudson::World::Scene* startScene = engine->GetSceneManager()->LoadScene("menu.scene");
    // TODO: startScene.resManager.loadTexture, startScene.resManager.loadShader etc - Brandon B
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

    Hudson::Entity::GameObject* hud = new Hudson::Entity::GameObject();
    hud->SetName("Text");
    hud->AddComponent(Text1);
    Hudson::Entity::GameObject::Transform transform = { glm::vec2(-10,100), glm::vec2(1,1), 0 };
    hud->SetTransform(transform);
    startScene->AddObject(hud);

    Hudson::Entity::GameObject* hud2 = new Hudson::Entity::GameObject();
    hud2->SetName("Text");
    hud2->AddComponent(Text2);
    transform = { glm::vec2(-10,200), glm::vec2(1,1), 0 };
    hud2->SetTransform(transform);
    startScene->AddObject(hud2);


    std::cout << "DemoGame: engine has been set up!\n";
}


int main() {
    Init();

    // Set up game scene/resources
    GameSetup();

    // Run engine loop until it is shut down
    engine->Run();

    //engine->RegisterMidFrameHook([&](Hudson::Common::Engine* engine) {
    //    //bool jumping = engine->GetInputManager()->getActionState("Jump");
    //    /*if (jumping)
    //    {
    //        playerPhysics->SetAcceleration({ 0, 5 }, true);
    //    }*/
    //    });

    // Clean up
    engine->Cleanup();
    delete engine;
}
