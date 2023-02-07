#pragma once

#include <Hudson.h>

enum laserState
{
	CHARGING,
	FIRING,
	DEACTIVATING
};

class LaserBehaviour : public Hudson::Entity::Behaviour
{
public:
	LaserBehaviour(glm::vec2 spawnPos);
	~LaserBehaviour();

	void Charge();
	void DeActivate();
	void OnCreate();

	Hudson::Render::SpriteComponent* LaserSprite;
	Hudson::Physics::ColliderComponent* CollisionBox;

private:
	void OnTick(const double& dt) override;
	void Firing(float deltaTime);
};

