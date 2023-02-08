#include <iostream>
#include <Hudson.h>
//#include "DemoBehaviour.h"
#include "AiAgent.h"
#include "MenuButton.h"
#include "Player.h"
#include "PickupWeapon.h"
#include "SettingsButton.h"
#include "AbilityHolder.h"
#include "PickupAbilitys.h"
#include "PassivePickups.h"
#include "Chest.h"
#include "Rooms/Room.h"
#include "WeaponDisplayUI.h"
#include "PlayerHealthUI.h"
#include "AbilityDisplayUI.h"
#include "PickupBehaviour.h"
#include "MeleeAttack.h"
#include "Projectile.h"
#include "MeleeCollider.h"
#include "CameraDolly.h"
#include "PauseMenu.h"

#include "Rooms/Room.h"
#include "Door.h"

Hudson::Common::Engine* engine;

#ifdef _DEBUG
#define ENABLE_EDITOR
#endif

#ifdef ENABLE_EDITOR
#pragma message("Creating an editor build")
#endif

#ifdef ENABLE_EDITOR
Hudson::Editor::Editor* editor;
#endif

//Hudson::Render::Camera* _defaultCamera = new Hudson::Render::Camera(0.0f, 1600.0f, 900.0f, 0.0f, -50.0f, 50.0f);

//UI Scenes
Hudson::Render::SpriteComponent* ButtonSprite;
Hudson::Render::SpriteComponent* backgroundImage;
Hudson::Render::SpriteComponent* SettingsMarkerImage;

//AI
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

Hudson::Render::SpriteComponent* weaponPickupSprite;
Hudson::Physics::ColliderComponent* weaponPickupCollider;

// TODO: this *needs* to move to Hudson ASAP
Hudson::Common::ResourceManager* resManager;

void InitRegistry()
{
    Hudson::Common::ComponentRegistry* registry = engine->GetComponentRegistry();
    registry->RegisterEngineComponents();
    registry->Register<Player>("PlayerTest");
    registry->Register<AiAgent>("AiBehavior");
    registry->Register<MenuButton>("ButtonBehaviour");
    registry->Register<SettingsButton>("SettingButtonBehaviour");
    registry->Register<Room>("Room");
    registry->Register<WeaponDisplayUI>("WeaponUIDisplay");
    registry->Register<PlayerHealthUI>("HealthUI");
    registry->Register<AbilityDisplayUI>("AbilityUI");
    registry->Register<Chest>("Chest");
    registry->Register<PassivePickups>("PassivePickups");
    registry->Register<AbilityHolder>("Ability");
    registry->Register<PickupAbilitys>("AbiltyPickup");
    registry->Register<PickupBehaviour>("Pickup");
    registry->Register<PickupWeapon>("WeaponPickUp");
    registry->Register<MeleeAttack>("MeleeBehaviour");
    registry->Register<Projectile>("ProjectileUpdatedBehaviour");
    registry->Register<MeleeCollider>("MeleeCollision");
    registry->Register<CameraDolly>("CameraDollyBehaviour");
    registry->Register<Door>("DoorBehaviour");
    registry->Register<PauseMenu>("Pause");
}

void Init() 
{
    Hudson::Util::Debug::RegisterAbortHandler();

    Hudson::Common::ResourceManager::SetupInstance(); // Set up single resource manager (TODO: decide per-scene/per-game)
    resManager = Hudson::Common::ResourceManager::GetInstance();

    engine = new Hudson::Common::Engine();

#ifdef ENABLE_EDITOR
    editor = new Hudson::Editor::Editor(engine); 
#endif
    engine->Setup();
    InitRegistry();
    engine->GetRenderer()->SetupDefaultShaders();

#ifdef ENABLE_EDITOR
    engine->GetInputManager()->SetEditorRef(editor);
    engine->GetSceneManager()->SetPaused(false);
#endif
}

void GameSetup()
{
    //engine->GetRenderer()->SetCamera(_defaultCamera);
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
    resManager->LoadTexture("textures/Test.png", true, "MainButtonImage");
    resManager->LoadTexture("textures/TempBackground.png", true, "backgroundImage");
    resManager->LoadTexture("textures/SettingsMarker.png", true, "SettingsMarkerImage");
    resManager->LoadTexture("textures/Passives.png", true, "Passives");
    resManager->LoadTexture("textures/Chest.png", true, "Chest");
    resManager->LoadTexture("textures/MenuCheckBox.png", true, "CheckBox");

    ButtonSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("MainButtonImage"));
    ButtonSprite->SetGridSize(glm::vec2(1, 1));

    SettingsMarkerImage = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
    SettingsMarkerImage->SetGridSize(glm::vec2(1, 1));

    backgroundImage = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("backgroundImage"));
    backgroundImage->SetDepthOrder(-1);
    backgroundImage->SetGridSize(glm::vec2(1, 1));

    // Load initial scene from file 
    // TODO: Hudson::World::Scene* startScene = engine->GetSceneManager()->LoadScene("menu.scene");
    // TODO: startScene.resManager.loadTexture, startScene.resManager.loadShader etc - Brandon B
    Hudson::World::Scene* TestScene = new Hudson::World::Scene();

    Hudson::World::Scene* startScene = new Hudson::World::Scene();

    Hudson::World::Scene* SettingsScene = new Hudson::World::Scene();

    engine->GetSceneManager()->AddScene(TestScene);

    Hudson::Entity::GameObject* player = new Hudson::Entity::GameObject();
    player->AddComponent(new Player(glm::vec2(500, 500)));
    player->SetName("Player");
    startScene->AddObject(player);

    Hudson::Entity::GameObject* MainCameraDolly = new Hudson::Entity::GameObject();
    MainCameraDolly->AddComponent(new CameraDolly(engine->GetInputManager()));
    MainCameraDolly->SetName("Camera");
    TestScene->AddObject(MainCameraDolly);
    SettingsScene->AddObject(MainCameraDolly);
    startScene->AddObject(MainCameraDolly);
    Hudson::Entity::GameObject* _PickupAbilitys = new Hudson::Entity::GameObject();
    _PickupAbilitys->AddComponent(new PickupAbilitys(glm::vec2(500, 500)));
    _PickupAbilitys->SetName("Player");
    startScene->AddObject(_PickupAbilitys);

    Hudson::Entity::GameObject* room = new Hudson::Entity::GameObject();
    room->SetName("Room");
    room->AddComponent(new class Room("Rooms/roomJson.room"));
    startScene->AddObject(room);

    Hudson::Entity::GameObject* PlayButton = new Hudson::Entity::GameObject();
    PlayButton->AddComponent(new MenuButton("Play", startScene, engine->GetInputManager(), vec2(70,60)));
    PlayButton->SetName("PlayButton");
    TestScene->AddObject(PlayButton);
    SettingsScene->AddObject(PlayButton);
    PlayButton->GetTransform().pos.x = 100.0f;
    PlayButton->GetTransform().pos.y = 100.0f;

    Hudson::Entity::GameObject* MainSettingsButton = new Hudson::Entity::GameObject();
    MainSettingsButton->AddComponent(new MenuButton("Settings", SettingsScene, engine->GetInputManager(), vec2(45,60)));
    MainSettingsButton->SetName("SettingsButton");
    TestScene->AddObject(MainSettingsButton);
    MainSettingsButton->GetTransform().pos.x = 100.0f;
    MainSettingsButton->GetTransform().pos.y = 300.0f;

    Hudson::Entity::GameObject* SettingsMarker = new Hudson::Entity::GameObject();
    SettingsMarker->AddComponent(new SettingsButton(engine->GetInputManager()));
    SettingsScene->AddObject(SettingsMarker);

    Hudson::Entity::GameObject* Background = new Hudson::Entity::GameObject();
    Background->AddComponent(backgroundImage);
    TestScene->AddObject(Background);
    SettingsScene->AddObject(Background);
    Background->GetTransform().scale.x = 1600.0f;
    Background->GetTransform().scale.y = 900.0f;


    #ifdef ENABLE_EDITOR
        ToolData toolData;
        toolData.function = StartRoomMaker;
        toolData.isRepeatingFunction = true;
        editor->AddTool("Room Maker", toolData);
    #endif

    std::cout << "Game: engine has been set up!\n";
}

void ToolFunc()
{
    std::cout << "Hello" << std::endl;
}

void RoomGameSetup()
{
    //engine->GetRenderer()->SetCamera();
    resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");
    resManager->LoadTexture("textures/PlayerSpriteSheet.png", true, "Player");


    Hudson::World::Scene* startScene = new Hudson::World::Scene();
    engine->GetSceneManager()->AddScene(startScene);

    Hudson::Entity::GameObject* room = new Hudson::Entity::GameObject();
    room->SetName("Room");
    room->AddComponent(new class Room("Rooms/roomJson.room"));
    startScene->AddObject(room);

	#ifdef ENABLE_EDITOR
	    ToolData toolData;
	    toolData.function = StartRoomMaker;
	    toolData.isRepeatingFunction = true;
	    editor->AddTool("Room Maker", toolData);
	#endif

}


int main() {
    Init();

    // Set up game scene/resources
    GameSetup();
    //RoomGameSetup();

    // Run engine loop until it is shut down
    engine->Run();

    // Clean up
    engine->Cleanup();
    delete engine;
}
