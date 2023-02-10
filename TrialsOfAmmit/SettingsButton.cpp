#include "SettingsButton.h"

SettingsButton::SettingsButton(Hudson::Input::InputManager* InputRef) : Behaviour("SettingButtonBehaviour")
{
	_inputManager = InputRef;
}

SettingsButton::~SettingsButton()
{

}

void SettingsButton::FromJson(const nlohmann::json& j)
{
}

void SettingsButton::ToJson(nlohmann::json& j)
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
	_buttonTextObject = new Hudson::Render::TextComponent("Fonts\\arial.ttf", resManager->GetShader("textShader"));
	_buttonTextObject->SetText(to_string(static_cast<int>(_resolution[_currentResIndex].x)) + "X" + to_string(static_cast<int>(_resolution[_currentResIndex].y)));
	_buttonTextObject->SetColor(vec3(1, 1, 1));
	_buttonTextObject->SetDepthOrder(2);
	Hudson::Entity::GameObject* MenuText = new Hudson::Entity::GameObject();
	MenuText->AddComponent(_buttonTextObject);
	MenuText->GetTransform().scale = vec2(1, 1);
	MenuText->GetTransform().pos.x = 75.0f;
	MenuText->GetTransform().pos.y = 170.0f;
	_parent->GetScene()->AddObject(MenuText);

	//sets up audio settings
	//audio forward button setup
	_buttonSprite2 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
	_buttonSprite2->SetGridSize(glm::vec2(2, 1));
	_buttonSprite2->SetGridPos(vec2(1, 1));
	_buttonSprite2->SetDepthOrder(1);
	MenuForwardAudio = new Hudson::Entity::GameObject();
	MenuForwardAudio->AddComponent(_buttonSprite2);
	MenuForwardAudio->GetTransform().pos.x = 310.0f;
	MenuForwardAudio->GetTransform().pos.y = 500.0f;
	_parent->GetScene()->AddObject(MenuForwardAudio);
	//audio back button setup
	_buttonSprite3 = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("SettingsMarkerImage"));
	_buttonSprite3->SetGridSize(glm::vec2(2, 1));
	_buttonSprite3->SetGridPos(vec2(0, 1));
	_buttonSprite3->SetDepthOrder(1);
	MenuBackAudio = new Hudson::Entity::GameObject();
	MenuBackAudio->AddComponent(_buttonSprite3);
	MenuBackAudio->GetTransform().pos.x = 90.0f;
	MenuBackAudio->GetTransform().pos.y = 500.0f;
	_parent->GetScene()->AddObject(MenuBackAudio);
	//sets the transform scale for the parent game object
	_parent->GetTransform().scale.x = 100.0f;
	_parent->GetTransform().scale.y = 100.0f;
	_parent->GetTransform().pos.x = 100.0f;
	_parent->GetTransform().pos.y = 500.0f;
	//sets up the text object and sets it to a game object and sets the object to the scene
	_buttonTextObjectAudio = new Hudson::Render::TextComponent("Fonts\\arial.ttf", resManager->GetShader("textShader"));
	_buttonTextObjectAudio->SetText("Audio Test");
	_buttonTextObjectAudio->SetColor(vec3(1, 1, 1));
	_buttonTextObjectAudio->SetDepthOrder(2);
	Hudson::Entity::GameObject* MenuTextAudio = new Hudson::Entity::GameObject();
	MenuTextAudio->AddComponent(_buttonTextObjectAudio);
	MenuTextAudio->GetTransform().scale = vec2(0.9, 0.9);
	MenuTextAudio->GetTransform().pos.x = 82.0f;
	MenuTextAudio->GetTransform().pos.y = 270.0f;
	_parent->GetScene()->AddObject(MenuTextAudio);

	//creates forward button and sets componants
	_buttonSpriteFullScreen = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("CheckBox"));
	_buttonSpriteFullScreen->SetGridSize(glm::vec2(2, 1));
	_buttonSpriteFullScreen->SetGridPos(vec2(0, 1));
	_buttonSpriteFullScreen->SetDepthOrder(1);
	FullScreen = new Hudson::Entity::GameObject();
	FullScreen->AddComponent(_buttonSpriteFullScreen);
	FullScreen->GetTransform().pos.x = 95.0f;
	FullScreen->GetTransform().pos.y = 650.0f;
	_parent->GetScene()->AddObject(FullScreen);
	//sets the transform scale for the parent game object
	_parent->GetTransform().scale.x = 100.0f;
	_parent->GetTransform().scale.y = 100.0f;
	_parent->GetTransform().pos.x = 100.0f;
	_parent->GetTransform().pos.y = 300.0f;
	//sets up the text object and sets it to a game object and sets the object to the scene
	_buttonTextObjectFullScreen = new Hudson::Render::TextComponent("Fonts\\arial.ttf", resManager->GetShader("textShader"));
	_buttonTextObjectFullScreen->SetText("Full Screen");
	_buttonTextObjectFullScreen->SetColor(vec3(1, 1, 1));
	_buttonTextObjectFullScreen->SetDepthOrder(2);
	Hudson::Entity::GameObject* FullScreenText = new Hudson::Entity::GameObject();
	FullScreenText->AddComponent(_buttonTextObjectFullScreen);
	FullScreenText->GetTransform().scale = vec2(1, 1);
	FullScreenText->GetTransform().pos.x = 80.0f;
	FullScreenText->GetTransform().pos.y = 345.0f;
	_parent->GetScene()->AddObject(FullScreenText);

	_audioMan = GetAudioManager();

	//stops the button clicking once per frame
	_clicked = false;
	_fullScreen = false;
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
			_audioMan->playSound("audio/UIMenuClick.wav", false, 0);
			Forawrd();
		}
	}
	//gets the back button position and calls the resolution back fucntion once clicked
	if (_inputManager->getWorldMPos().x >= MenuBack->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuBack->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuBack->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuBack->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			_audioMan->playSound("audio/UIMenuClick.wav", false, 0);
			Back();
		}
	}

	//gets the forward button position and calls the Audio forward fucntion once clicked
	if (_inputManager->getWorldMPos().x >= MenuForwardAudio->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuForwardAudio->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuForwardAudio->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuForwardAudio->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			_audioMan->playSound("audio/UIMenuClick.wav", false, 0);
			ForawrdAudio();
		}
	}
	//gets the back button position and calls the Audio back fucntion once clicked
	if (_inputManager->getWorldMPos().x >= MenuBackAudio->GetTransform().pos.x && _inputManager->getWorldMPos().x <= MenuBackAudio->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= MenuBackAudio->GetTransform().pos.y && _inputManager->getWorldMPos().y <= MenuBackAudio->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			_audioMan->playSound("audio/UIMenuClick.wav", false, 0);
			BackAudio();
		}
	}

	//sets the fullscreen to the opposite
	if (_inputManager->getWorldMPos().x >= FullScreen->GetTransform().pos.x && _inputManager->getWorldMPos().x <= FullScreen->GetTransform().pos.x + 50 && _inputManager->getWorldMPos().y >= FullScreen->GetTransform().pos.y && _inputManager->getWorldMPos().y <= FullScreen->GetTransform().pos.y + 50)
	{
		if (_inputManager->getM1Click() && _clicked == false)
		{
			_audioMan->playSound("audio/UIMenuClick.wav", false, 0);
			SetFullScreen();
		}
	}
	//timer to make sure that button is not clicked multiple times 
	if (_clicked == true)
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

void SettingsButton::ForawrdAudio()
{
	//TODO set audio manager volume
}

void SettingsButton::BackAudio()
{
	//TODO set audio manager volume
}

void SettingsButton::SetFullScreen()
{
	if (_fullScreen)
	{
		_fullScreen = false;
		_buttonSpriteFullScreen->SetGridPos(vec2(0, 1));	
#ifdef _DEBUG
		
#else 
		int xpos, ypos, width, height;
		glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(),& xpos, &ypos, &width, &height);
		glfwSetWindowAttrib(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), GLFW_DECORATED, GLFW_TRUE);
		glfwSetWindowAttrib(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), GLFW_MAXIMIZED, GLFW_FALSE);
		glfwSetWindowPos(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), width/4, height/4);
#endif
	}
	else
	{
		_fullScreen = true;
		_buttonSpriteFullScreen->SetGridPos(vec2(1, 1));
#ifdef _DEBUG
		
#else 
		glfwSetWindowAttrib(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), GLFW_DECORATED, GLFW_FALSE);
		glfwSetWindowAttrib(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), GLFW_MAXIMIZED, GLFW_TRUE);
		glfwSetWindowPos(GetEngine()->GetRenderer()->GetWindow()->GetWindow(), 0, 0);
#endif
	}
	_clicked = true;
}

void SettingsButton::DrawPropertyUI()
{
}
