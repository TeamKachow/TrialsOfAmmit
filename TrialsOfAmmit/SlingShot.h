#pragma once
#include "BaseWeaponClass.h"
#include "WeaponType.h"
#include "Projectile.h"
#include <Hudson.h>

class SlingShot : public BaseWeaponClass
{
public:
	SlingShot();
	~SlingShot();
	WeaponTypes _weaponType;
	float _projectileRange;;
	Hudson::Entity::GameObject* _projectile;
	float _projectileMovementSpeed;
	void Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene) override;
};

