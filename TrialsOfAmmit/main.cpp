#include <iostream>
#include <Hudson.h>
//#include "DemoBehaviour.h"
#include "AiAgent.h"
#include "MenuButton.h"
#include "Player.h"
#include "PickupWeapon.h"

#include "AbilityHolder.h"
#include "PickupAbilitys.h"


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
Hudson::Render::SpriteComponent* Sprite4;
Hudson::Render::SpriteComponent* Sprite5;
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
    registry->Register<Player>("PlayerTest");
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
    engine->GetRenderer()->SetupDefaultShaders();
}

void GameSetup()
{
    engine->GetRenderer()->SetCamera(_defaultCamera);

    resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");
    resManager->LoadTexture("textures/ArrowSpriteSheet.png", true, "Projectile");
    resManager->LoadTexture("textures/RockSpriteSheet.png", true, "Rock");
    resManager->LoadTexture("textures/PlayerSpriteSheet.png", true, "Player");
    resManager->LoadTexture("textures/MeleeSpriteSheet.png", true, "Slash");
    resManager->LoadTexture("textures/WeaponSpriteSheet.png", true, "Weapon");
    resManager->LoadTexture("textures/UIFrame.png", true, "UIFrame");
    resManager->LoadTexture("textures/HealthBar.png", true, "HealthBar");
    resManager->LoadTexture("textures/Abilitys.png", true, "Abilitys");
    resManager->LoadTexture("textures/Blood.png", true, "Blood");
    resManager->LoadTexture("textures/Grave.png", true, "Grave");
    resManager->LoadTexture("textures/InvisSpriteSheet.png", true, "Invis");
    resManager->LoadTexture("textures/Test.png", true, "Test");
    resManager->LoadTexture("textures/TempBackground.png", true, "Background");

    //Text = new Hudson::Render::TextComponent(_defaultCamera->GetProjectionMatrix(),glm::vec2(20,20));
    //Text->SetText("Top Text");
    //Text->SetColor(glm::vec3(0, 400, 0));


    Sprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
    Sprite1->SetGridSize(glm::vec2(3, 4));

    Sprite2 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
    Sprite2->SetGridSize(glm::vec2(3, 4));

    Sprite3 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Test"));
    Sprite3->SetGridSize(glm::vec2(1, 1));

    Sprite5 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Test"));
    Sprite5->SetGridSize(glm::vec2(1, 1));

    Sprite4 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Background"));
    Sprite4->SetDepthOrder(-1);
    Sprite4->SetGridSize(glm::vec2(1, 1));

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

    Hudson::World::Scene* SettingsScene = new Hudson::World::Scene();
    //engine->GetSceneManager()->AddScene(startScene);

    Hudson::Entity::GameObject* blah = new Hudson::Entity::GameObject();
    blah->AddComponent(Sprite2);
	blah->AddComponent(Physics1);
    blah->AddComponent(Collider1);
    blah->AddComponent(new AiAgent(Sprite2, 0.8));
    blah->SetName("AI1");
    startScene->AddObject(blah);
    blah->GetTransform().pos.x = 200.0f;

    Hudson::Entity::GameObject* blah2 = new Hudson::Entity::GameObject();
    blah2->AddComponent(Sprite1);
    blah2->AddComponent(Physics2);
    blah2->AddComponent(Collider2);
    blah2->AddComponent(new AiAgent(Sprite1, 0.8));
    blah2->SetName("AI2");
    startScene->AddObject(blah2);

    blah2->GetTransform().pos.x = 1400.0f;

    Hudson::Entity::GameObject* player = new Hudson::Entity::GameObject();
    player->AddComponent(new Player(glm::vec2(500, 500)));

    player->SetName("Player");
    startScene->AddObject(player);
    
    Hudson::Entity::GameObject* WeaponPickup = new Hudson::Entity::GameObject();
    WeaponPickup->AddComponent(new PickupWeapon(glm::vec2(300.0f, 300.0f), WeaponPickup));
    startScene->AddObject(WeaponPickup);

    Hudson::Entity::GameObject* WeaponPickup1 = new Hudson::Entity::GameObject();
    WeaponPickup1->AddComponent(new PickupWeapon(glm::vec2(400.0f, 300.0f), WeaponPickup1));
    startScene->AddObject(WeaponPickup1);

    Hudson::Entity::GameObject* AbilityPickup = new Hudson::Entity::GameObject();
    AbilityPickup->AddComponent(new PickupAbilitys(glm::vec2(500.0f, 300.0f), AbilityPickup));
    startScene->AddObject(AbilityPickup);

    Hudson::Entity::GameObject* PlayButton = new Hudson::Entity::GameObject();
    PlayButton->AddComponent(Sprite3);
    PlayButton->AddComponent(new MenuButton(Sprite3, glm::vec2(200,100), "Play", startScene, engine->GetInputManager(), vec2(70,60)));
    PlayButton->SetName("PlayButton");
    TestScene->AddObject(PlayButton);
    PlayButton->GetTransform().pos.x = 100.0f;
    PlayButton->GetTransform().pos.y = 100.0f;

    Hudson::Entity::GameObject* SettingsButton = new Hudson::Entity::GameObject();
    SettingsButton->AddComponent(Sprite5);
    SettingsButton->AddComponent(new MenuButton(Sprite5, glm::vec2(200, 100), "Settings", SettingsScene, engine->GetInputManager(), vec2(45,60)));
    SettingsButton->SetName("SettingsButton");
    TestScene->AddObject(SettingsButton);
    SettingsButton->GetTransform().pos.x = 100.0f;
    SettingsButton->GetTransform().pos.y = 300.0f;

    Hudson::Entity::GameObject* Background = new Hudson::Entity::GameObject();
    Background->AddComponent(Sprite4);
    TestScene->AddObject(Background);
    Background->GetTransform().scale.x = 1600.0f;
    Background->GetTransform().scale.y = 900.0f;

    std::cout << "Game: engine has been set up!\n";
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
