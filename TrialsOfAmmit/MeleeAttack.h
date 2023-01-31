#pragma once
#include <Hudson.h>
#include "facingDirection.h"

class MeleeAttack : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	MeleeAttack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene, Hudson::Entity::GameObject* _slashRef);
	~MeleeAttack();

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	Hudson::Render::SpriteComponent* _slashSprite;
	Hudson::Entity::GameObject* _slash;
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

