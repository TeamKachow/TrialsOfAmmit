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
	//gets instance of resource manager
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	//sets up render resolutions settings
	//creates forward button and sets componants
	_buttonSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
	_buttonSprite->SetGridSize(glm::vec2(2, 1));
	_buttonSprite->SetGridPos(vec2(1, 1));
	_buttonSprite->SetDepthOrder(1);
	MenuForward = new Hudson::Entity::GameObject();
	MenuForward->AddComponent(_buttonSprite);
	MenuForward->GetTransform().pos.x = 310.0f;
	MenuForward->GetTransform().pos.y = 300.0f;
	_parent->GetScene()->AddObject(MenuForward);
	//creates back button and sets componants
	_buttonSprite1 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
	_buttonSprite1->SetGridSize(glm::vec2(2, 1));
	_buttonSprite1->SetGridPos(vec2(2, 1));
	_buttonSprite1->SetDepthOrder(1);
	MenuBack = new Hudson::Entity::GameObject();
	MenuBack->AddComponent(_buttonSprite1);
	MenuBack->GetTransform().pos.x = 90.0f;
	MenuBack->GetTransform().pos.y = 300.0f;
	_parent->GetScene()->AddObject(MenuBack);
	//sets the transform scale for the parent game object
	_parent->GetTransform().scale.x = 100.0f;
	_parent->GetTransform().scale.y = 100.0f;
	_parent->GetTransform().pos.x = 100.0f;
	_parent->GetTransform().pos.y = 300.0f;
	//sets up the text object and sets it to a game object and sets the object to the scene
	_buttonTextObject = new Hudson::Render::TextComponent("Fonts\\arial.ttf", glm::vec2(0, 0));
	_buttonTextObject->SetText(to_string(static_cast<int>(_resolution[_currentResIndex].x)) + "X" + to_string(static_cast<int>(_resolution[_currentResIndex].y)));
	_buttonTextObject->SetColor(vec3(1, 1, 1));
	_buttonTextObject->SetDepthOrder(2);
	Hudson::Entity::GameObject* MenuText = new Hudson::Entity::GameObject();
	MenuText->AddComponent(_buttonTextObject);
	MenuText->GetTransform().scale = vec2(1, 1);
	MenuText->GetTransform().pos.x = 150.0f;
	MenuText->GetTransform().pos.y = 350.0f;
	_parent->GetScene()->AddObject(MenuText);

	//sets up audio settings
	//audio forward button setup
	MenuForwardAudio = new Hudson::Entity::GameObject();
	MenuForwardAudio->AddComponent(_buttonSprite);
	MenuForwardAudio->GetTransform().pos.x = 310.0f;
	MenuForwardAudio->GetTransform().pos.y = 500.0f;
	_parent->GetScene()->AddObject(MenuForwardAudio);
	//audio back button setup
	MenuBackAudio = new Hudson::Entity::GameObject();
	MenuBackAudio->AddComponent(_buttonSprite1);
	MenuBackAudio->GetTransform().pos.x = 90.0f;
	MenuBackAudio->GetTransform().pos.y = 500.0f;
	_parent->GetScene()->AddObject(MenuBackAudio);
	//sets the transform scale for the parent game object
	_parent->GetTransform().scale.x = 100.0f;
	_parent->GetTransform().scale.y = 100.0f;
	_parent->GetTransform().pos.x = 100.0f;
	_parent->GetTransform().pos.y = 500.0f;
	//sets up the text object and sets it to a game object and sets the object to the scene
	_buttonTextObjectAudio = new Hudson::Render::TextComponent("Fonts\\arial.ttf", glm::vec2(0, 0));
	_buttonTextObjectAudio->SetText("Audio Test");
	_buttonTextObjectAudio->SetColor(vec3(1, 1, 1));
	_buttonTextObjectAudio->SetDepthOrder(2);
	Hudson::Entity::GameObject* MenuTextAudio = new Hudson::Entity::GameObject();
	MenuTextAudio->AddComponent(_buttonTextObjectAudio);
	MenuTextAudio->GetTransform().scale = vec2(1, 1);
	MenuTextAudio->GetTransform().pos.x = 150.0f;
	MenuTextAudio->GetTransform().pos.y = 550.0f;
	_parent->GetScene()->AddObject(MenuTextAudio);
	//stops the button clicking once per frame
	_clicked = false;
}

void SettingsButton::OnDestroy()
{
}

void SettingsButton::OnTick(const double& dt)
{
	//gets the forward button position and calls the resolution forward fucntion once clicked
	if (_inputManager->getWorldMPos().x >= MenuForward->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuForward->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuForward->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuForward->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			
			Forawrd();
		}
	}
	//gets the back button position and calls the resolution back fucntion once clicked
	if (_inputManager->getWorldMPos().x >= MenuBack->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuBack->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuBack->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuBack->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			Back();
		}
	}
	//timer to make sure that button is not clicked multiple times 
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
	//itterates the index number for the resolution array and sets it to the render window 
	_currentResIndex++;
	if (_currentResIndex > 5)
	{
		_currentResIndex = 5;
	}
	glfwSetWindowSize(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), _resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	GetEngine()->GetRenderer()->CreateFramebuffers(_resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	//sets resolution to the text output
	_buttonTextObject->SetText(to_string(static_cast<int>(_resolution[_currentResIndex].x)) + "X" + to_string(static_cast<int>(_resolution[_currentResIndex].y)));
	_clicked = true;
}

void SettingsButton::Back()
{
	//itterates the index number for the resolution array and sets it to the render window 
	_currentResIndex--;
	if (_currentResIndex < 0)
	{
		_currentResIndex = 0;
	}
	glfwSetWindowSize(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), _resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	GetEngine()->GetRenderer()->CreateFramebuffers(_resolution[_currentResIndex].x, _resolution[_currentResIndex].y);
	//sets resolution to the text output
	_buttonTextObject->SetText(to_string(static_cast<int>(_resolution[_currentResIndex].x)) + "X" + to_string(static_cast<int>(_resolution[_currentResIndex].y)));
	_clicked = true;
}

void SettingsButton::DrawPropertyUI()
{
}
