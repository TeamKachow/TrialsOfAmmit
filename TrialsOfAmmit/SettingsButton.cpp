#include "SettingsButton.h"

SettingsButton::SettingsButton(Hudson::Input::InputManager* InputRef) : Behaviour("SettingButtonBehaviour")
{
	_inputManager = InputRef;

}

SettingsButton::~SettingsButton()
{

}

void SettingsButton::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	_buttonSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
	_buttonSprite->SetGridSize(glm::vec2(2, 1));
	_buttonSprite->SetGridPos(vec2(1, 1));
	_buttonSprite->SetDepthOrder(1);
	MenuForward = new Hudson::Entity::GameObject();
	MenuForward->AddComponent(_buttonSprite);
	MenuForward->GetTransform().pos.x = 300.0f;
	MenuForward->GetTransform().pos.y = 300.0f;
	_parent->GetScene()->AddObject(MenuForward);

	_buttonSprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
	_buttonSprite1->SetGridSize(glm::vec2(2, 1));
	_buttonSprite1->SetGridPos(vec2(2, 1));
	_buttonSprite1->SetDepthOrder(1);
	MenuBack = new Hudson::Entity::GameObject();
	MenuBack->AddComponent(_buttonSprite1);
	MenuBack->GetTransform().pos.x = 100.0f;
	MenuBack->GetTransform().pos.y = 300.0f;
	_parent->GetScene()->AddObject(MenuBack);

	_parent->GetTransform().scale.x = 100.0f;
	_parent->GetTransform().scale.y = 100.0f;
	_parent->GetTransform().pos.x = 100.0f;
	_parent->GetTransform().pos.y = 300.0f;

	_buttonTextObject = new Hudson::Render::TextComponent("Fonts\\arial.ttf", glm::vec2(0, 0));
	_buttonTextObject->SetText("Test");
	_buttonTextObject->SetColor(vec3(1, 1, 1));
	_buttonTextObject->SetDepthOrder(2);
	Hudson::Entity::GameObject* MenuText = new Hudson::Entity::GameObject();
	MenuText->AddComponent(_buttonTextObject);
	MenuText->GetTransform().scale = vec2(1, 1);
	MenuText->GetTransform().pos.x = 200.0f;
	MenuText->GetTransform().pos.y = 350.0f;
	_parent->GetScene()->AddObject(MenuText);

	_clicked = false;
}

void SettingsButton::OnDestroy()
{
}

void SettingsButton::OnTick(const double& dt)
{
	if (_inputManager->getWorldMPos().x >= MenuForward->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuForward->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuForward->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuForward->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			
			Forawrd();
		}
	}

	if (_inputManager->getWorldMPos().x >= MenuBack->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuBack->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuBack->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuBack->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			Back();
		}
	}
	if (_clicked)
	{
		_timer += dt;
		if (_timer > _resetTime)
		{
			_clicked = false;
			_timer = 0;
		}
	}
}

void SettingsButton::Forawrd()
{
	_currentResIndex++;
	if (_currentResIndex > 5)
	{
		_currentResIndex = 5;
	}
	glfwSetWindowSize(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), _resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	GetEngine()->GetRenderer()->CreateFramebuffers(_resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	_clicked = true;
}

void SettingsButton::Back()
{
	_currentResIndex--;
	if (_currentResIndex < 0)
	{
		_currentResIndex = 0;
	}
	glfwSetWindowSize(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), _resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	GetEngine()->GetRenderer()->CreateFramebuffers(_resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	_clicked = true;
}

void SettingsButton::DrawPropertyUI()
{
}
