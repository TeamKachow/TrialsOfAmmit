#pragma once
#include <Hudson.h>

using namespace std;
using namespace glm;

enum ButtonAction
{
	PLAY,
	BACK,
	SETTINGS,
	QUIT
};

class MenuButton : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	MenuButton(Hudson::Render::SpriteComponent* ButtonSprite, vec2 Scale, string Text, ButtonAction Action, Hudson::Common::Engine* Engine);
	~MenuButton();
	Hudson::Render::SpriteComponent* _buttonSprite;
	Hudson::Render::TextComponent* _buttonTextObject;
	Hudson::World::Scene* _currentScene;
	Hudson::Common::Engine* _engine;
	Hudson::Input::InputManager _inputManager;
	vec2 _buttonScale;
	string _buttonText;

protected:
	ButtonAction _currentButtonAction;


private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void OnClickPlay();
	void OnClickBack();
	void OnClickSettings();
	void OnClickQuit();
	bool _clicked;
};

