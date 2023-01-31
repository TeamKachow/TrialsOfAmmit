#pragma once
#include <Hudson.h>
#include "BaseWeaponClass.h"
#include "Axe.h"
#include "Khopesh.h"
#include "facingDirection.h"
#include "Bow.h"
#include "Projectile.h"
class Player : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
private:
	Hudson::Render::SpriteComponent* _playerSprite;
	double _playerAnimSpeed = 0.2;
	double _playerAnimTimer = 0;
	double _testTimer = 0;
	double _playerFireRate = 0.9;
	float _playerHealth = 100.0f;
	Hudson::Physics::PhysicsComponent* _playerPhysics;
	Hudson::World::Scene* _currentScene;
	int _gridX = 0;
	int _gridY = 0;
	facingDirections _playerDirection = Down;
	Hudson::Entity::GameObject* _projectile;

	Axe _axe;
	Khopesh _khopesh;
	Bow _bow;

	BaseWeaponClass* _playersWeapon = &_axe;

	void Fire();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void StopMove();
	void AnimMove();

	
public:
	Player(Hudson::Render::SpriteComponent* playerSprite, double animSpeed = 0.8);
	~Player() override;
	void TakeDamage(float _damageTaken);

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;

	void DrawPropertyUI() override;



};

