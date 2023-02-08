#include "PauseMenu.h"

PauseMenu::PauseMenu(glm::vec2 spawnPos, Hudson::World::Scene* sceneToPause, Player* player) : Behaviour ("Pause")
{
	_inputManager = new Hudson::Input::InputManager();
	_sceneToPause = sceneToPause;
	_player = player;
	_isKeyRelease = false;
	_canRun = false;
	_canRun2 = false;
	Timer = 0;
	UpPauseTimer = 1;
	
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::OnCreate()
{

}

void PauseMenu::OnTick(const double& dt)
{
	//Checks for the keypress from the inital player press to finish
	if (!_inputManager->getActionState("Pause"))
	{
		_canRun = true;
	}

	//If the key has been release - checks for a 2nd key press and once that is release will run the Unpause Function
	if (_canRun = true)
	{
		if (_inputManager->getActionState("Pause"))
		{
			if (_canRun2)
			{
				_sceneToPause->SetActive(true);
			}
		}
		else
		{
			_canRun2 = true;
		}

	}
}

void PauseMenu::OnDestroy()
{
}

void PauseMenu::PauseScene()
{
	_sceneToPause->SetActive(false);
	_player->_isPaused = true;
	_canRun = false;
	_canRun2 = false;
	Timer = 0;
}

void PauseMenu::DrawPropertyUI()
{
}

void PauseMenu::FromJson(const nlohmann::json& j)
{
}

void PauseMenu::ToJson(nlohmann::json& j)
{
}
