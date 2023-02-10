#include "MainMenu.h"
#include "MenuButton.h"
#include "SettingsButton.h"



MainMenu::MainMenu(Hudson::Input::InputManager* InputRef, Hudson::World::Scene* playScene, Hudson::World::Scene* settingScene) : Behaviour("MainMenuBehavoiur")
{
    _playscene = playScene;
    _settingScene = settingScene;
    _inputManager = InputRef;
        

}

MainMenu::~MainMenu()
{
}

void MainMenu::DrawPropertyUI()
{
}

void MainMenu::OnCreate()
{
    Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

    Hudson::Entity::GameObject* PlayButton = new Hudson::Entity::GameObject();
    _parent->GetScene()->AddObject(PlayButton);
    _settingScene->AddObject(PlayButton);
    PlayButton->AddComponent(new MenuButton("Play", _playscene, _inputManager, vec2(-15, -20)));
    PlayButton->SetName("PlayButton");

    PlayButton->GetTransform().pos.x = 100.0f;
    PlayButton->GetTransform().pos.y = 100.0f;

    Hudson::Entity::GameObject* MainSettingsButton = new Hudson::Entity::GameObject();
    _parent->GetScene()->AddObject(MainSettingsButton);
    MainSettingsButton->AddComponent(new MenuButton("Settings", _settingScene, _inputManager, vec2(-30, -120)));
    MainSettingsButton->SetName("SettingsButton");

    MainSettingsButton->GetTransform().pos.x = 100.0f;
    MainSettingsButton->GetTransform().pos.y = 300.0f;

    Hudson::Entity::GameObject* SettingsMarker = new Hudson::Entity::GameObject();
    SettingsMarker->AddComponent(new SettingsButton(_inputManager));
    _settingScene->AddObject(SettingsMarker);

    _background = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("backgroundImage"));
    _background->SetDepthOrder(-1);
    _background->SetGridSize(glm::vec2(1, 1));

    Hudson::Entity::GameObject* Background = new Hudson::Entity::GameObject();
    Background->AddComponent(_background);
    _parent->GetScene()->AddObject(Background);
    _settingScene->AddObject(Background);
    Background->GetTransform().scale.x = 1600.0f;
    Background->GetTransform().scale.y = 900.0f;
}

void MainMenu::OnDestroy()
{
}

void MainMenu::OnTick(const double& dt)
{
}

void MainMenu::FromJson(const nlohmann::json& j)
{
}

void MainMenu::ToJson(nlohmann::json& j)
{
}
