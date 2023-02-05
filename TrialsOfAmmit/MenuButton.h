#pragma once
#include <Hudson.h>

using namespace std;
using namespace glm;


class MenuButton : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	MenuButton(Hudson::Render::SpriteComponent* ButtonSprite, vec2 Scale, string Text, Hudson::World::Scene* NextScene);
	~MenuButton();
	Hudson::Render::SpriteComponent* _buttonSprite;
	Hudson::Render::TextComponent* _buttonTextObject;
	Hudson::World::Scene* _currentScene;
	Hudson::Input::InputManager _inputManager;
	Hudson::World::Scene* _nextScene;
	vec2 _buttonScale;
	string _buttonText;

protected:


private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void OnClick();
	bool _clicked;
};

