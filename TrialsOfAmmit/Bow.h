#pragma once
#include "BaseWeaponClass.h"
#include "Projectile.h"
#include <Hudson.h>

class Bow : public BaseWeaponClass
{
public:
	Hudson::Entity::GameObject* _projectile;
	Bow();
	~Bow();
	void Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene) override;

};

