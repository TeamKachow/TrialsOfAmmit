#pragma once
#include <string>
#include <glm/vec2.hpp>
#include "Hudson.h"
#include "facingDirection.h"

class BaseWeaponClass
{
private:

protected:

public:
	BaseWeaponClass();
	~BaseWeaponClass();
	virtual void Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene);
	std::string _weaponName;
	float _weaponAttackSpeed;
	float _weaponAttackDamage;


};


