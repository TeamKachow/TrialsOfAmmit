#pragma once

#include <Hudson.h>
#include "Player.h"

enum fireState
{
	IGNITE,
	BURN,
	EXTINGUISH
};

class FireBehaviour : public Hudson::Entity::Behaviour
{
public:
	FireBehaviour(glm::vec2 spawnPos = { 100,100 });
	~FireBehaviour();

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	Hudson::Render::SpriteComponent* FireSprite;
	Hudson::Physics::ColliderComponent* CollisionBox;
	Hudson::Entity::GameObject* flame;

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;

protected:
	Hudson::World::Scene* _currentScene;
	Player* _player;
	fireState _currentState;
	glm::vec2 _spawnPos;
	double _igniteTimer;
	double _BurnTimer;
	double _extinguishTimer;
	bool _playerDamaged;
};

