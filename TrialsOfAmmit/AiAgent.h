#pragma once

#include <Hudson.h>
#include "Player.h"
#include "AiMelee.h"
#include "BaseWeaponClass.h"
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

//enum facingDirections
//{
//	UP,
//	DOWN,
//	LEFT,
//	RIGHT
//};

class AiAgent : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:  
	AiAgent(Hudson::Render::SpriteComponent* aiSprite, double animSpeed);
	~AiAgent();
	void TakeDamage(int damageAmount);
	Hudson::Render::SpriteComponent* _aiSprite;
	float _maxHealth;
	float _currentHealth;
	float _meleeDamage;
	virtual void AiDead();
	float _maxSpeed;

protected:
	void CollisionCheck();
	void Animate(float deltaTime);
	virtual void AiAttack();
	AiMelee _melee;
	BaseWeaponClass* _aiWeapon = &_melee;
	vector<Hudson::Physics::PhysicsComponent*>_aiPhysicsComponent;
	Hudson::World::Scene* _currentScene;
	Player* _player;
	AiState _currentState;
	vec2 _target;
	vec2 _moveForce;
	vec2 _velocity;
	vec2 _acceleration;
	float _distanceFromTarget;
	float _distanceFromPlayer;
	facingDirections _facingDirection;
	float _currentSpeed;
	
	float _mass;
	float _maxRange;
	float _minRange;
	float _attackTimer;
	double _aiAnimSpeed;
	double _aiAnimTimer;
	bool _alive;
	bool _arrive;

private: 

	void OnTick(const double& dt) override;
	void OnCreate() override;
	void OnDestroy() override;
	void OnTick(const double& dt) override;
	void DrawPropertyUI() override;
	void RandomTargetSelector();
	void Move(float deltatime);
	void GetPlayerPos();
	void SetPlayerPos();
	vec2 Seek(vec2 Target);
	vec2 Wander(vec2 Target);
};

