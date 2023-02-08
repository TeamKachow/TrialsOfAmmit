#pragma once
#include <Hudson.h>
#include "facingDirection.h"
#include "WeaponType.h"
class Projectile : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:

	Projectile(facingDirections projectileDirection = {Down}, glm::vec2 spawnPos = {0,0}, Hudson::World::Scene* CurrentScene = {nullptr}, WeaponTypes _weaponFiring = { WT_Bow }, float _damage = {0}, float _projectileSpeed = {0}, float _range = {0});
	~Projectile()override;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	Hudson::World::Scene* _currentScene;
	Hudson::Physics::PhysicsComponent* _projectilePhysics;
	Hudson::Render::SpriteComponent* _projectileSprite;
	Hudson::Physics::ColliderComponent* _projectileCollider;
	facingDirections _projectileDirection;

	WeaponTypes _currentWeaponFiring;
	float _projectileDamage;
	float _projectileMoveSpeed;
	float _projectileRange;
	glm::vec2 _spawnPos;


	float _animTimer;
	float _animSpeed;

	float _deleteTimer;
	float _deleteTime;

	int _gridX;
	int _gridY;


	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;

	void DrawPropertyUI() override;
};

