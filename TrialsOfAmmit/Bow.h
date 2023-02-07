#pragma once
#include "RangedBaseWeaponClass.h"
#include "WeaponType.h"
#include "Projectile.h"
#include <Hudson.h>

class Bow : public RangedBaseWeaponClass
{
public:
	Bow();
	~Bow();
	void UpgradeWeapon(WeaponUpgradeTypes Level) override;
	void Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, float _playerDamageMod) override;
};

