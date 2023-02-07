#include "Bow.h"

#include <iostream>

Bow::Bow()
{
	_weaponAttackDamage = 60;
	_weaponAttackSpeed = 0.5;
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
		_weaponAttackDamage = 60;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 0.5;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 65;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 0.5;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 70;
		_projectileMovementSpeed = 500;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 0.75;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 75;
		_projectileMovementSpeed = 600;
		_projectileRange = 1.5;
		_weaponAttackSpeed = 0.75;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 80;
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
	_projectile->AddComponent(new Projectile(projectileDirection, spawnPos, CurrentScene, WT_Bow, _weaponAttackDamage, _projectileMovementSpeed, _projectileRange));
	CurrentScene->AddObject(_projectile);
	std::cout << "Player Has Attacked With Bow" << "\n";

	
}

