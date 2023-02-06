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
	Hudson::Input::InputManager _inputManager;
	Hudson::Physics::PhysicsComponent* _playerPhysics;
	Hudson::World::Scene* _currentScene;

	//Anim Variables
	double _playerAnimSpeed = 0.2;
	double _playerAnimTimer = 0;
	int _gridX = 0;
	int _gridY = 0;

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

	//Anim Functions
	void AnimMove();
	void OnDeath();

	
public:
	Hudson::Render::SpriteComponent* _playerSprite;
	//Accessable player Stats
	BaseWeaponClass* _playersWeapon = &_axe;
	float _playerMovementSpeed = 45.0;
	float _playerHealth = 100.0f;
	bool _godMode;

	void TakeDamage(float _damageTaken);

	Player(Hudson::Render::SpriteComponent* playerSprite, double animSpeed = 0.8);
	~Player() override;
	
	//Base Needed Functions
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;



};

