#pragma once
#include <Hudson.h>
#include <random>
#include "Player.h"
#include "AiMelee.h"
#include "PickupWeapon.h"

enum LocustState
{
	LS_SEEK,
	LS_DEAD
};

class LocustBehaviour : public Hudson::Entity::Behaviour
{
public:
	LocustBehaviour(glm::vec2 spawnPos = { 0, 0 });
	~LocustBehaviour();
	virtual void AiDead();
	float _maxSpeed;
	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	void Kill();

protected:
	void CollisionCheck();
	void Animate(float deltaTime);
	AiMelee _melee;
	BaseWeaponClass* _aiWeapon = &_melee;
	Hudson::Render::SpriteComponent* _aiSprite;
	Hudson::Render::SpriteComponent* _aiDeathSprite;
	Hudson::Physics::PhysicsComponent* _aiPhysicsComponent;
	Hudson::World::Scene* _currentScene;
	Hudson::Physics::ColliderComponent* _aiCollider;
	Hudson::Physics::ColliderComponent* _aiColliderWall;
	Player* _player;
	LocustState _currentState;
	glm::vec2 _target;
	glm::vec2 _moveForce;
	glm::vec2 _velocity;
	glm::vec2 _acceleration;
	float _distanceFromTarget;
	float _distanceFromPlayer;
	facingDirections _facingDirection;
	float _currentSpeed;
	glm::vec2 _spawnPosition;
	float _mass;
	double _animationTimer;
	double _aiAnimDeathTimer;
	bool _alive;
	bool _arrive;
	Hudson::Entity::GameObject* Blood;

private:
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void Move(float deltatime);
	void SetPlayerPos();
	glm::vec2 Seek(glm::vec2 Target);
	glm::vec2 _lastFramePos;
};

