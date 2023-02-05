#include "MenuButton.h"

MenuButton::MenuButton(Hudson::Render::SpriteComponent* ButtonSprite, vec2 Scale, string Text, ButtonAction Action, Hudson::Common::Engine* Engine) : Behaviour("ButtonBehaviour")
{
	_buttonSprite - ButtonSprite;
	_buttonScale = Scale;
	_buttonText = Text;
	_currentButtonAction = Action;
	_engine = Engine;
}

MenuButton::~MenuButton()
{

}

void MenuButton::OnCreate()
{
	_parent->GetTransform().scale = (_buttonScale);
	_buttonTextObject = new Hudson::Render::TextComponent(glm::vec2(_parent->GetTransform().pos.x + 70, _parent->GetTransform().pos.y + 60 ));
	_buttonTextObject->SetText(_buttonText);
	_buttonTextObject->SetColor(vec3(1, 1, 1));
	Hudson::Entity::GameObject* MenuText = new Hudson::Entity::GameObject();
	MenuText->AddComponent(_buttonTextObject);
	MenuText->GetTransform().scale = vec2(1, 1);
	_currentScene = _parent->GetScene();
	_currentScene->AddObject(MenuText);
	cout << _parent->GetTransform().pos.x << _parent->GetTransform().pos.y << endl;
	_clicked = false;
}

void MenuButton::OnDestroy()
{

}

void MenuButton::OnTick(const double& dt)
{
	if (_inputManager.getM1Click())
	{
		cout << _parent->GetTransform().pos.x - 70 << endl;
		cout << _parent->GetTransform().pos.y - 235 << endl;
	}
	//cout << _inputManager.getMPos().y << endl;
	switch (_currentButtonAction)
	{
	case PLAY:
		//if(_inputManager.getMPos().x >= 630 && _inputManager.getMPos().x <= 730 && _inputManager.getMPos().y >= 265 && _inputManager.getMPos().y <= 310)
		if (_inputManager.getMPos().x >= _parent->GetTransform().pos.x - 70 && _inputManager.getMPos().x <= _parent->GetTransform().pos.x - 70 + 100 && _inputManager.getMPos().y >= _parent->GetTransform().pos.y - 235 && _inputManager.getMPos().y <= _parent->GetTransform().pos.y - 235 + 45)
		{ 
			if (_inputManager.getM1Click() && _clicked == false)
			{
				OnClickPlay();
			}
		}
		break;
	case BACK:
		break;
	case SETTINGS:
		break;
	case QUIT:
		//figure it out
		break;
	default:
		break;
	}
}

void MenuButton::DrawPropertyUI()
{
	_buttonTextObject->DrawPropertyUI();
}

void MenuButton::OnClickPlay()
{
	cout << "Play CLicked" << endl;
	Hudson::World::Scene* TestScene = new Hudson::World::Scene();
	_engine->GetSceneManager()->AddScene(TestScene);
	_clicked = true;
}

void MenuButton::OnClickBack()
{

}

void MenuButton::OnClickSettings()
{

}

void MenuButton::OnClickQuit()
{

}