#pragma once

#include <Hudson.h>
#include "Player.h"

enum laserState
{
	CHARGING,
	FIRING,
	DEACTIVATING
};

class LaserBehaviour : public Hudson::Entity::Behaviour
{
public:
	LaserBehaviour(glm::vec2 spawnPos, int laserType);
	~LaserBehaviour();

	void Charge();
	void DeActivate();

	Hudson::Render::SpriteComponent* LaserSprite;
	Hudson::Physics::ColliderComponent* CollisionBox;

private:
	void OnCreate() override;
	//void OnDestroy() override;
	//void OnTick(const double& dt) override;
	void Firing(float deltaTime);

protected:
	void CollisionCheck();
	void Animate(float deltaTime);
	std::vector<Hudson::Physics::PhysicsComponent*>_aiPhysicsComponent;
	Hudson::World::Scene* _currentScene;
	Player* _player;
	laserState _currentState;
	int _laserType;
	float _currentSpeed;
};

