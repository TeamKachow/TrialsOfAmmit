#pragma once
#include <Hudson.h>
#include "Player.h"
class PlayerHealthUI : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PlayerHealthUI(glm::vec2 spawnPos, Hudson::World::Scene* _scene, Player* _player);
	PlayerHealthUI(glm::vec2 spawnPos = { 100.0f, 25.0f }, Hudson::World::Scene* _scene = nullptr, Player* _player = nullptr);
	~PlayerHealthUI();

	Hudson::Render::SpriteComponent* _healthUISprite;
	Hudson::World::Scene* _currentScene;
	Player* _currentPlayer;

	float _playerHealthScale;

	glm::uvec2 _currentPos;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

};

