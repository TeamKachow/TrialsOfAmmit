#pragma once

#include <Hudson.h>

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
	AiAgent();
	~AiAgent();
	float _maxHealth;
	float _currentHealth;
	float _meleeDamage;

protected:
	bool CollisionCheck();
	virtual void AiAttack();
	virtual void AiDead();
	vector<Hudson::Physics::PhysicsComponent*>_aiPhysicsComponent;
	AiState _currentState;
	vec2 _target;
	vec2 _moveForce;
	vec2 _velocity;
	vec2 _acceleration;
	vec2 _position;
	float _distanceFromTarget;
	float _currentSpeed;
	float _maxSpeed;
	float _mass;
	bool _alive;

private: 
	void OnTick(const double& dt) override;
	void RandomTargetSelector();
	//These return types may be wrong 
	vec2 Seek(vec2 Target);
	vec2 Wander(vec2 Target);
};

