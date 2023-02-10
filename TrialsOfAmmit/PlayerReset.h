#pragma once
#include <Hudson.h>
#include "Player.h"
class PlayerReset : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PlayerReset(glm::vec2 spawnPos = { 100,100 }, Hudson::World::Scene* sceneToPause = { nullptr }, Player* player = { nullptr });
	~PlayerReset();
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;
	void PauseScene();

	float Timer;
	float UpPauseTimer;
	bool _canRun;
	bool _canRun2;
	Player* _player;

	Hudson::Input::InputManager* _inputManager;
	Hudson::World::Scene* _sceneToPause;

	bool _isKeyRelease;

	
};

