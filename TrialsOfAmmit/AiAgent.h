#pragma once

#include <Hudson.h>
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
	double _aiAnimSpeed;
	double _aiAnimTimer;
	float _maxHealth;
	float _currentHealth;
	float _meleeDamage;

protected:
	void CollisionCheck();
	void Animate(float deltaTime);
	virtual void AiAttack();
	virtual void AiDead();
	vector<Hudson::Physics::PhysicsComponent*>_aiPhysicsComponent;
	AiState _currentState;
	vec2 _target;
	vec2 _moveForce;
	vec2 _velocity;
	vec2 _acceleration;
	float _distanceFromTarget;
	float _currentSpeed;
	float _maxSpeed;
	float _mass;
	bool _alive;
	bool _arrive;

private: 
	void OnTick(const double& dt) override;
	void OnCreate() override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	void RandomTargetSelector();
	void Move(float deltatime);
	vec2 Seek(vec2 Target);
	vec2 Wander(vec2 Target);
};

