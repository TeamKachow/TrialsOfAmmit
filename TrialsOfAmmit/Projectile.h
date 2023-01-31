#pragma once
#include <Hudson.h>
#include "facingDirection.h"
class Projectile : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	
	Projectile(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, Hudson::Entity::GameObject* _projectileRef);
	~Projectile()override;

	Hudson::World::Scene* _currentScene;
	Hudson::Entity::GameObject* _projectile;
	Hudson::Physics::PhysicsComponent* _projectilePhysics;
	Hudson::Render::SpriteComponent* _projectileSprite;
	facingDirections _projectileDirection;

	glm::vec2 _spawnPos;

	float _animTimer;
	float _animSpeed;

	float _deleteTimer;
	float _deleteTime;

	int _gridX;
	int _gridY;




	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;

	void DrawPropertyUI() override;
};

