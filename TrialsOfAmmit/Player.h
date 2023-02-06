#pragma once
#include <Hudson.h>
#include "BaseWeaponClass.h"
#include "Axe.h"
#include "Khopesh.h"
#include "facingDirection.h"
#include "Bow.h"
#include "Spear.h"
#include "Projectile.h"
#include "SlingShot.h"
class Player : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
private:
	//Set up Components
	Hudson::Render::SpriteComponent* _playerSprite;
	Hudson::Input::InputManager _inputManager;
	//Hudson::Physics::PhysicsComponent* _playerPhysics;
	Hudson::Physics::PhysicsComponent* playerPhysics;
	Hudson::World::Scene* _currentScene;
	Hudson::Physics::ColliderComponent* playerCollider;
	//Hudson::Entity::GameObject* _player;

	Hudson::Render::SpriteComponent* GraveSprite;

	float deathTimer;
	float deathAnim;
	int _deathGridX;

	//Anim Variables
	double _playerAnimSpeed = 0.2;
	double _playerAnimTimer = 0;
	int _gridX = 0;
	int _gridY = 0;

	bool _isDead;

	//Attack Timer
	double _attackTimer = 0;

	//Movement and Facing Directions
	facingDirections _playerDirection = Stopped;
	facingDirections _playerFacingDirection = Down;

	//Weapons (Baseclass holding the players Weapons - Rest are Set up)
	SlingShot _slingshot;
	Axe _axe;
	Khopesh _khopesh;
	Spear _spear;
	Bow _bow;
	

	//Actions
	void Fire();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void StopMove();

	void CreateUI();
	void HealthBarUI();

	void Respawn();

	//Anim Functions
	void AnimMove();
	void OnDeath();

	
public:
	//Accessable player Stats
	BaseWeaponClass* _playersWeapon = &_axe;
	float _playerMovementSpeed = 45.0;
	float _playerHealth = 100.0f;
	bool _godMode;

	void TakeDamage(float _damageTaken);
	Player(const Player& other) = default;
	Player(glm::vec2 spawnPos = glm::vec2(0,0));
	~Player() override;
	
	//Base Needed Functions
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;



};

