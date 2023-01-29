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
	AiState _currentState;
	vec2 _target;
	vector<Hudson::Physics::PhysicsComponent*>_aiPhysicsComponent;

private: 
	void OnTick(const double& dt) override;
	//These return types may be wrong 
	vec2 Seek(vec2 Target);
	vec2 Wander(vec2 Target);

};

