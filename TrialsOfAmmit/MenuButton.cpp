#include "MenuButton.h"

MenuButton::MenuButton(string Text, Hudson::World::Scene* NextScene, Hudson::Input::InputManager* InputRef, vec2 textOffset) : Behaviour("ButtonBehaviour")
{
	_buttonScale = vec2(200,100);
	_buttonText = Text;
	_nextScene = NextScene;
	_inputManager = InputRef;
	_textOffset = textOffset;
}

MenuButton::~MenuButton()
{

}

void MenuButton::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_buttonSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("MainButtonImage"));
	_parent->AddComponent(_buttonSprite);
	_parent->GetTransform().scale = (_buttonScale);
	_buttonTextObject = new Hudson::Render::TextComponent("Fonts\\arial.ttf",glm::vec2(0, 0));
	_buttonTextObject->SetText(_buttonText);
	_buttonTextObject->SetColor(vec3(1, 1, 1));
	_buttonTextObject->SetDepthOrder(2);
	Hudson::Entity::GameObject* MenuText = new Hudson::Entity::GameObject();
	MenuText->AddComponent(_buttonTextObject);
	MenuText->GetTransform().scale = vec2(1, 1);
	_currentScene = _parent->GetScene();
	_currentScene->AddObject(MenuText);
	MenuText->GetTransform().pos = vec2(_parent->GetTransform().pos.x + +_textOffset.x, _parent->GetTransform().pos.y + _textOffset.y);
	_clicked = false;
	_nextScene->SetActive(false);
}

void MenuButton::OnDestroy()
{

}

void MenuButton::OnTick(const double& dt)
{
	
	if (_inputManager->getWorldMPos().x >= _parent->GetTransform().pos.x && _inputManager->getWorldMPos().x <= _parent->GetTransform().pos.x + 200 && _inputManager->getWorldMPos().y >= _parent->GetTransform().pos.y && _inputManager->getWorldMPos().y <= _parent->GetTransform().pos.y + 100)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			if (_nextScene->IsActive() == false)
			{
				OnClick();
			}
			return;
		}
	}
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