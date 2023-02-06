#include <iostream>

#include <Hudson.h>

//#include "DemoBehaviour.h"
#include "AiAgent.h"
#include "MenuButton.h"
#include "Player.h"
#include "PickupWeapon.h"
#include <Render/Renderer.h>

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

Hudson::Render::Camera* _defaultCamera = new Hudson::Render::Camera(0.0f, 1600.0f, 900.0f, 0.0f, -50.0f, 50.0f);

Hudson::Render::SpriteComponent* Sprite1;
Hudson::Render::SpriteComponent* Sprite2;
Hudson::Render::SpriteComponent* Sprite3;
Hudson::Physics::PhysicsComponent* Physics1;
Hudson::Physics::PhysicsComponent* Physics2;
Hudson::Physics::ColliderComponent* Collider1;
Hudson::Physics::ColliderComponent* Collider2;

Hudson::Render::TextComponent* Text;

//Player 
Hudson::Render::SpriteComponent* playerSprite;
Hudson::Physics::PhysicsComponent* playerPhysics;
Hudson::Physics::ColliderComponent* playerCollider;

Hudson::Render::SpriteComponent* weaponPickupSprite;
Hudson::Physics::ColliderComponent* weaponPickupCollider;

// TODO: this *needs* to move to Hudson ASAP
Hudson::Common::ResourceManager* resManager;

void InitRegistry()
{
    registry = new Hudson::Editor::ComponentRegistry();
    registry->RegisterEngineComponents();

    //registry->Register<DemoBehaviour>("Demo Behaviour");
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
    engine->GetRenderer()->SetCamera(_defaultCamera);

    
    // TODO put these 2 files in line so doesnt need to be called in main.cpp - sorry Brandon B
    resManager->LoadShader("../HudsonEngine/Render/shaders/textVert.glsl", "../HudsonEngine/Render/shaders/textFrag.glsl", std::string("textShader"));
    resManager->LoadShader("../HudsonEngine/Render/shaders/renderTextureVert.glsl", "../HudsonEngine/Render/shaders/renderTextureFrag.glsl", std::string("screenShader"));

    // This one stays
    resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

    // Shader needs to be Use() to pass values over
 //   resManager->GetShader("spriteShader")->Use().SetMatrix4("projection", _defaultCamera->GetProjectionMatrix());

    resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");
    resManager->LoadTexture("textures/ArrowSpriteSheet.png", true, "Projectile");
    resManager->LoadTexture("textures/RockSpriteSheet.png", true, "Rock");
    resManager->LoadTexture("textures/PlayerSpriteSheet.png", true, "Player");
    resManager->LoadTexture("textures/MeleeSpriteSheet.png", true, "Slash");
    resManager->LoadTexture("textures/WeaponSheet.png", true, "Weapon");
    resManager->LoadTexture("textures/InvisSpriteSheet.png", true, "Invis");
    resManager->LoadTexture("textures/Test.png", true, "Test");

    playerSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Player"));
    playerSprite->SetSize(glm::vec2(64.0f, 64.0f));
    playerSprite->SetGridSize(glm::vec2(3, 4));
    playerSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

    playerPhysics = new Hudson::Physics::PhysicsComponent();
    playerPhysics->SetMass(1.0f);
    playerPhysics->SetForce(glm::vec2(0.0, 0));
    playerPhysics->SetAcceleration(glm::vec2(0, 0), true);
    playerPhysics->SetVelocity(glm::vec2(0, 0));

    playerCollider = new Hudson::Physics::ColliderComponent();

    weaponPickupSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Weapon"));
    weaponPickupSprite->SetSize(glm::vec2(16.0f, 16.0f));
    weaponPickupSprite->SetGridSize(glm::vec2(5, 1));
    weaponPickupSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    weaponPickupCollider = new Hudson::Physics::ColliderComponent();

    Text = new Hudson::Render::TextComponent(glm::vec2(20,20));



    Sprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
    Sprite1->SetSize(glm::vec2(64.0f, 64.0f));
    Sprite1->SetGridSize(glm::vec2(3, 4));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Sprite2 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
    Sprite2->SetSize(glm::vec2(64.0f, 64.0f));
    Sprite2->SetGridSize(glm::vec2(3, 4));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Sprite3 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Test"));
    //Sprite3->SetSize(glm::vec2(128.0f, 64.0f));
    Sprite3->SetGridSize(glm::vec2(1, 1));
    //Sprite1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Physics1 = new Hudson::Physics::PhysicsComponent();
    Physics1->SetMass(1.0f);
    Physics1->SetForce(glm::vec2(10.0, 0));
    Physics1->SetAcceleration(glm::vec2(10, 0), true);
    Physics1->SetVelocity(glm::vec2(0, 0));

    Physics2 = new Hudson::Physics::PhysicsComponent();
    Physics2->SetMass(1.0f);
    Physics2->SetForce(glm::vec2(-10.0, 0));
    Physics2->SetAcceleration(glm::vec2(-100, 0), true);
    Physics2->SetVelocity(glm::vec2(-100, 0));

    Collider1 = new Hudson::Physics::ColliderComponent();
    Collider2 = new Hudson::Physics::ColliderComponent();

    // Load initial scene from file 
    // TODO: Hudson::World::Scene* startScene = engine->GetSceneManager()->LoadScene("menu.scene");
    // TODO: startScene.resManager.loadTexture, startScene.resManager.loadShader etc - Brandon B
    Hudson::World::Scene* TestScene = new Hudson::World::Scene();
    engine->GetSceneManager()->AddScene(TestScene);

    Hudson::World::Scene* startScene = new Hudson::World::Scene();
    //engine->GetSceneManager()->AddScene(startScene);

    Hudson::Entity::GameObject* blah = new Hudson::Entity::GameObject();
    blah->AddComponent(Sprite2);
	blah->AddComponent(Physics1);
    blah->AddComponent(Collider1);
    blah->AddComponent(new AiAgent(Sprite2, 0.8));
    blah->SetName("AI1");
    startScene->AddObject(blah);
    blah->GetTransform().pos.x = 200.0f;

 /*   Hudson::Entity::GameObject* blah2 = new Hudson::Entity::GameObject();
    blah2->AddComponent(Sprite1);
    blah2->AddComponent(Physics2);
    blah2->AddComponent(Collider2);
    blah2->AddComponent(new AiAgent(Sprite1, 0.8));
    blah2->SetName("AI2");
    startScene->AddObject(blah2);

    blah2->GetTransform().pos.x = 1400.0f;*/
    //auto WeaponPickups = new Hudson::Entity::GameObject();
   // WeaponPickups->AddComponent(new PickupWeapon(WeaponPickups));
    //startScene->AddObject(WeaponPickups);

    Hudson::Entity::GameObject* player = new Hudson::Entity::GameObject();
    player->AddComponent(playerSprite);
    player->AddComponent(new Player(playerSprite));
    player->AddComponent(playerPhysics);
    player->AddComponent(playerCollider);
    player->SetName("Player");
    startScene->AddObject(player);


    player->GetTransform().pos.x = 500.0f;
    player->GetTransform().pos.y = 500.0f;

    Hudson::Entity::GameObject* WeaponPickup = new Hudson::Entity::GameObject();
    WeaponPickup->AddComponent(weaponPickupSprite);
    WeaponPickup->AddComponent(new PickupWeapon());
    WeaponPickup->AddComponent(weaponPickupCollider);
    WeaponPickup->SetName("WeaponPickup");
    startScene->AddObject(WeaponPickup);


    WeaponPickup->GetTransform().pos.x = 600.0f;
    WeaponPickup->GetTransform().pos.y = 600.0f;

    Hudson::Entity::GameObject* Button = new Hudson::Entity::GameObject();
    Button->AddComponent(Sprite3);
    Button->AddComponent(weaponPickupCollider);
    Button->AddComponent(new MenuButton(Sprite3, glm::vec2(200,100), "Play", startScene));
    Button->SetName("Button");
    TestScene->AddObject(Button);
    Button->GetTransform().scale.x = 128.0f;
    Button->GetTransform().scale.y = 64.0f;
    Button->GetTransform().pos.x = 700.0f;
    Button->GetTransform().pos.y = 500.0f;

    //Hudson::Entity::GameObject* text = new Hudson::Entity::GameObject();
    //text->AddComponent(Text);
    //startScene->AddObject(text);

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
