#include "MenuButton.h"
#include "Player.h"

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

void MenuButton::FromJson(const nlohmann::json& j)
{
}

void MenuButton::ToJson(nlohmann::json& j)
{
}

void MenuButton::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_buttonSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("MainButtonImage"));
	_parent->AddComponent(_buttonSprite);
	_parent->GetTransform().scale = (_buttonScale);

	_buttonTextObject = new Hudson::Render::TextComponent("Fonts\\arial.ttf",resManager->GetShader("textShader"));
	_buttonTextObject->SetText(_buttonText);
	_buttonTextObject->SetColor(vec3(1, 1, 1));
	_buttonTextObject->SetDepthOrder(2);

	Hudson::Entity::GameObject* MenuText = new Hudson::Entity::GameObject();
	MenuText->AddComponent(_buttonTextObject);
	MenuText->GetTransform().scale = vec2(1, 1);
	MenuText->GetTransform().pos = vec2(_parent->GetTransform().pos.x + _textOffset.x, _parent->GetTransform().pos.y + _textOffset.y);
	
	_clicked = false;
	_nextScene->SetActive(false);

	_currentScene = _parent->GetScene();
	_currentScene->AddObject(MenuText);
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
				cout << "Hit" << endl;
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
	//GetSceneManager()->RemoveScene(_currentScene);
	_parent->GetScene()->SetActive(false);
	_parent->GetScene()->SetRendering(false);

	auto _sceneObjects = _nextScene->GetObjects();

	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetComponent<Player>() != nullptr)
		{
			other->GetComponent<Player>()->OnCreate();
			
		}
	}
	

	

}