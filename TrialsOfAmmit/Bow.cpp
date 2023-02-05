#include "Bow.h"

#include <iostream>

Bow::Bow()
{
	_weaponAttackDamage = 20.0;
	_weaponAttackSpeed = 2;
	_projectileMovementSpeed = 500.0;
	_projectileRange = 1.5;
	_weaponType = WT_Bow;
	_weaponLevel = Wood;
}

Bow::~Bow()
{
}

void Bow::UpgradeWeapon(WeaponUpgradeTypes Level)
{
	switch (Level)
	{
	case Wood:
		_weaponAttackDamage = 20;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 2;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 25;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 1.75;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 35;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 1.5;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 40;
		_projectileMovementSpeed = 600;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 1.25;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 45;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 1;
		_weaponLevel = Gold;
		break;
	}
}

void Bow::Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene)
{
	_projectile = new Hudson::Entity::GameObject();
	_projectile->AddComponent(new Projectile(projectileDirection, spawnPos, CurrentScene, _projectile, WT_Bow, _weaponAttackDamage, _projectileMovementSpeed, _projectileRange));
	std::cout << "Player Has Attacked With Bow" << "\n";

	
}

