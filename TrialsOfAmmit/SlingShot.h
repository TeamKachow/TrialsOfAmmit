#pragma once
#include "RangedBaseWeaponClass.h"
#include "WeaponType.h"
#include "Projectile.h"
#include <Hudson.h>

class SlingShot : public RangedBaseWeaponClass
{
public:
	SlingShot();
	~SlingShot();
	void Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene) override;
};

