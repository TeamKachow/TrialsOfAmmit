#include "MenuButton.h"

MenuButton::MenuButton(Hudson::Render::SpriteComponent* ButtonSprite, vec2 Scale, string Text, Hudson::World::Scene* NextScene) : Behaviour("ButtonBehaviour")
{
	_buttonSprite - ButtonSprite;
	_buttonScale = Scale;
	_buttonText = Text;
	_nextScene = NextScene;
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
	_nextScene->SetActive(false);
}

void MenuButton::OnDestroy()
{

}

void MenuButton::OnTick(const double& dt)
{
	if (_inputManager.getM1Click())
	{
		cout << _inputManager.getMPos().x << endl;
		cout << _inputManager.getMPos().y << endl;
	}
	
	//if (_inputManager.getMPos().x >= _parent->GetTransform().pos.x)
	//{
		//cout << "hit" << endl;
		if (_inputManager.getM1Click() && _clicked == false)
		{
			if (_nextScene->IsActive() == false)
			{
				OnClick();
			}
			return;
		}
	//}
}

void MenuButton::DrawPropertyUI()
{
	_buttonTextObject->DrawPropertyUI();
}

void MenuButton::OnClick()
{
	cout << "Play CLicked" << endl;
	_nextScene->SetActive(true);
	GetSceneManager()->AddScene(_nextScene);
	GetSceneManager()->RemoveScene(_currentScene);
}