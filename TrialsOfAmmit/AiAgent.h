#pragma once

#include <Hudson.h>
#include "Player.h"
#include <string.h>
#include <random>

using namespace glm;
using namespace std;

enum AiState
{
	SEEK,
	WANDER,
	ATTACK,
	DEAD
};

class AiAgent : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:  
	AiAgent(Hudson::Render::SpriteComponent* aiSprite, double animSpeed = 0.8);
	~AiAgent();
	void TakeDamage(int damageAmount);
	Hudson::Render::SpriteComponent* _aiSprite;
	float _maxHealth;
	float _currentHealth;
	float _meleeDamage;

protected:
	void CollisionCheck();
	void Animate(float deltaTime);
	virtual void AiAttack();
	virtual void AiDead();
	vector<Hudson::Physics::PhysicsComponent*>_aiPhysicsComponent;
	Hudson::World::Scene* _currentscene;
	Player* _player;
	AiState _currentState;
	vec2 _target;
	vec2 _moveForce;
	vec2 _velocity;
	vec2 _acceleration;
	float _distanceFromTarget;
	float _currentSpeed;
	float _maxSpeed;
	float _mass;
	float _maxRange;
	float _minRange;
	double _aiAnimSpeed;
	double _aiAnimTimer;
	bool _alive;
	bool _arrive;

private: 
	void OnTick(const double& dt) override;
	void OnCreate() override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	void RandomTargetSelector();
	void Move(float deltatime);
	void GetPlayerPos();
	vec2 Seek(vec2 Target);
	vec2 Wander(vec2 Target);
};

