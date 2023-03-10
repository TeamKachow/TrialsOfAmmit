#pragma once
#include <string>
#include <glm/vec2.hpp>
#include "Hudson.h"
#include "facingDirection.h"
#include "WeaponUpgrade.h"
#include "WeaponType.h"

class BaseWeaponClass
{
private:

protected:

public:
	BaseWeaponClass();
	~BaseWeaponClass();
	virtual void Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, float _playerDamageMod);
	virtual void AiAttack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene);
	virtual void UpgradeWeapon(WeaponUpgradeTypes Level);
	float _weaponAttackSpeed;
	float _weaponAttackDamage;
	WeaponTypes _weaponType;
	WeaponUpgradeTypes _weaponLevel;


};


