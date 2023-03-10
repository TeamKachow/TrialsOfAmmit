#pragma once

#include <Hudson.h>
#include "Player.h"

enum laserState
{
	IDLE,
	CHARGING,
	FIRING,
	DEACTIVATING
};

class LaserBehaviour : public Hudson::Entity::Behaviour
{
public:
	LaserBehaviour(glm::vec2 spawnPos = {100,100}, int laserType = {0});
	~LaserBehaviour();

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	void Charge();

	Hudson::Render::SpriteComponent* LaserSprite;
	Hudson::Physics::ColliderComponent* CollisionBox;
	Hudson::Entity::GameObject* Laser;

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;

protected:
	void Animate(float deltaTime);
	Hudson::World::Scene* _currentScene;
	Player* _player;
	laserState _currentState;
	int _laserType;
	double _chargeTimer;
	double _fireTimer;
	double _animTimer;
	double _deactivateTimer;
	double _laserCooldown;
	glm::vec2 _spawnPos;
};

