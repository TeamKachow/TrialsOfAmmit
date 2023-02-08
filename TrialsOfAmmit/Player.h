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
	Hudson::Physics::PhysicsComponent* playerPhysics;
	Hudson::World::Scene* _currentScene;
	Hudson::Physics::ColliderComponent* playerCollider;

	Hudson::World::Scene* _pauseScene;

	Hudson::Render::TextComponent* _pauseText;
	Hudson::Entity::GameObject* PauseText;

	Hudson::Render::SpriteComponent* GraveSprite;
	glm::vec2 _lastFramePos;
	glm::vec2 _lastLastFramePos;



	float _deathTimer;
	float _deathAnim;
	int _deathGridX;

	//Anim Variables
	double _playerAnimSpeed = 0.2;
	double _playerAnimTimer = 0;
	int _gridX = 0;
	int _gridY = 0;

	

	glm::vec2 _spawnPos;

	bool _isDamaged;
	bool _isDead;

	bool _isHittingUp;
	bool _isHittingDown;
	bool _isHittingRight;
	bool _isHittingLeft;

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
	void WallCollisions();
	void InverseForce();
	//Anim Functions
	void AnimMove();
	void OnDeath();

	
public:
	bool toPause;
	bool _isPaused;
	bool _pauseKeyIsDeactive;
	Hudson::Render::SpriteComponent* _playerSprite;

	Hudson::Entity::GameObject* _pauseMenu;
	//Accessable player Stats
	BaseWeaponClass* _playersWeapon = &_axe;
	float _maxHealth;
	float _playerMovementSpeed = 500;
	float _playerHealth = 100.0f;
	float _playerDamageMod;
	bool _godMode;

	void PassiveAddMaxHealth(float additionalHealth);
	void PassiveAddSpeed(float additionalSpeed);
	void PassiveAddDamageMod(float additionalDamage);

	void TakeDamage(float _damageTaken);
	Player(const Player& other) = default;
	Player(glm::vec2 spawnPos = glm::vec2(0,0));
	~Player() override;
	
	//Base Needed Functions
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;



};

