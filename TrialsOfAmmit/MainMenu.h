#pragma once
#include <Hudson.h>

using namespace std;
using namespace glm;

class MainMenu : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	MainMenu(Hudson::Input::InputManager* InputRef = { nullptr }, Hudson::World::Scene* playScene = {nullptr}, Hudson::World::Scene* settingScene = {nullptr});
	~MainMenu();
	void DrawPropertyUI() override;
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	Hudson::World::Scene* _playscene;
	Hudson::World::Scene* _settingScene;
	Hudson::Input::InputManager* _inputManager;

	Hudson::Render::SpriteComponent* _background;



protected:
private:

};

