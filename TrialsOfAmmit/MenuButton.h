#pragma once
#include <Hudson.h>

using namespace std;
using namespace glm;

class MenuButton : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	MenuButton(string Text = { " " }, Hudson::World::Scene* NextScene = { nullptr }, Hudson::Input::InputManager* InputRef = {nullptr}, vec2 textOffset = { 0, 0 });
	~MenuButton();
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;
	Hudson::Render::SpriteComponent* _buttonSprite;
	Hudson::Render::TextComponent* _buttonTextObject;
	Hudson::World::Scene* _currentScene;
	Hudson::Input::InputManager* _inputManager;
	Hudson::World::Scene* _nextScene;
	vec2 _buttonScale;
	string _buttonText;
	vec2 _textOffset;
	Hudson::Audio::AudioManager* _audioMan;

protected:

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void OnClick();
	bool _clicked;
};

