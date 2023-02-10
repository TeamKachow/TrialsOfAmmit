#include "PlayerReset.h"
#include "Door.h"

PlayerReset::PlayerReset(glm::vec2 spawnPos, Hudson::World::Scene* sceneToPause, Player* player) : Behaviour("PlayerReset")
{
	_inputManager = new Hudson::Input::InputManager();
	_sceneToPause = sceneToPause;
	_player = player;
	_isKeyRelease = false;
	_canRun = true;
	Timer = 0;
	UpPauseTimer = 1;
}

PlayerReset::~PlayerReset()
{
}

void PlayerReset::OnCreate()
{
}

void PlayerReset::OnTick(const double& dt)
{
	std::cout << "Is rUNnning " << "\n";
	if (_inputManager->getActionState("Respawn") && _player->_playerHealth <= 0)
	{
		
		_sceneToPause->SetActive(true);
		_player->Respawn();
		
		auto objs = _player->GetParent()->GetScene()->GetObjects();
		for (Hudson::Entity::GameObject* obj : objs)
		{
			if (obj->GetName() == "Door")
			{
				_player->GetParent()->GetTransform().pos = obj->GetTransform().pos;
			}
		}
		
		


	}
}

void PlayerReset::OnDestroy()
{
}

void PlayerReset::DrawPropertyUI()
{
}

void PlayerReset::FromJson(const nlohmann::json& j)
{
}

void PlayerReset::ToJson(nlohmann::json& j)
{
}

void PlayerReset::PauseScene()
{
	_sceneToPause->SetActive(false);
	_player->_isPaused = true;
	_canRun = false;
	Timer = 0;
}
