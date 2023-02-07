#pragma once
#include <Hudson.h>

using namespace std;
using namespace glm;

class SettingsButton : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	SettingsButton(Hudson::Input::InputManager* InputRef);
	~SettingsButton();
	Hudson::Render::SpriteComponent* _buttonSprite;
	Hudson::Render::SpriteComponent* _buttonSprite1;
	Hudson::World::Scene* _currentScene;
	Hudson::Input::InputManager* _inputManager;
	Hudson::World::Scene* _nextScene;
	Hudson::Render::TextComponent* _buttonTextObject;
	Hudson::Render::TextComponent* _buttonTextObjectAudio;

	vec2 _buttonScale;
	string _buttonText;
	vec2 _textOffset;
protected:



private:
	Hudson::Entity::GameObject* MenuForward;
	Hudson::Entity::GameObject* MenuBack;
	Hudson::Entity::GameObject* MenuForwardAudio;
	Hudson::Entity::GameObject* MenuBackAudio;
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void Forawrd();
	void Back();
	void DrawPropertyUI() override;
	bool _clicked;
	vec2 _resolution[6]{ vec2(1280,720), vec2(1366,768), vec2(1600,900), vec2(1920,1080), vec2(2560,1440), vec2(3840,2160) };
	int _currentResIndex = 0;
	float _timer;
	float _resetTime = 0.5;
};

