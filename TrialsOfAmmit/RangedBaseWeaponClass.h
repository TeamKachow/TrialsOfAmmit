#pragma once
#include "BaseWeaponClass.h"
class RangedBaseWeaponClass : public BaseWeaponClass
{
public:
	float _projectileMovementSpeed;
	float _projectileRange;
	Hudson::Entity::GameObject* _projectile;

};

