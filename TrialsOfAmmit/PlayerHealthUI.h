#pragma once
#include <Hudson.h>
#include "Player.h"
class PlayerHealthUI : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PlayerHealthUI(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject, Hudson::World::Scene* _scene, Player* _player);
	~PlayerHealthUI();

	Hudson::Entity::GameObject* _healthUI;
	Hudson::Render::SpriteComponent* _healthUISprite;
	Hudson::World::Scene* _currentScene;
	Player* _currentPlayer;

	float _playerHealthScale;

	glm::uvec2 _currentPos;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

};

