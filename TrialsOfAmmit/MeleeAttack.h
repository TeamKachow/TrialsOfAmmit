#pragma once
#include <Hudson.h>
#include "facingDirection.h"

class MeleeAttack : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	MeleeAttack(facingDirections slashDirection = { Down }, glm::vec2 playerPos = { 0,0 }, Hudson::World::Scene* currentScene = { nullptr });
	~MeleeAttack();

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	Hudson::Render::SpriteComponent* _slashSprite;
	facingDirections _slashDirection;
	glm::vec2 _playerPos;
	Hudson::World::Scene* _currentScene;

	float _animTimer;
	float _animSpeed;

	int _gridX;
	int _gridY;

	float _deleteTimer;
	float _deleteTime;
};

