#include "SlingShot.h"

SlingShot::SlingShot()
{
	_weaponAttackDamage = 15.0;
	_projectileMovementSpeed = 200;
	_projectileRange = 2.0;
	_weaponAttackSpeed = 0.75;
	_weaponType = WT_SlingShot;
}

SlingShot::~SlingShot()
{
}

void SlingShot::UpgradeWeapon(WeaponUpgradeTypes Level)
{
	switch (Level)
	{
	case Wood:
		_weaponAttackDamage = 15;
		_projectileMovementSpeed = 200;
		_projectileRange = 2.0;
		_weaponAttackSpeed = 0.75;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 20;
		_projectileMovementSpeed = 225;
		_projectileRange = 2.0;
		_weaponAttackSpeed = 0.7;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 25;
		_projectileMovementSpeed = 250;
		_projectileRange = 2.25;
		_weaponAttackSpeed = 0.65;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 30;
		_projectileMovementSpeed = 250;
		_projectileRange = 2.5;
		_weaponAttackSpeed = 0.6;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 35;
		_projectileMovementSpeed = 250;
		_projectileRange = 2.5;
		_weaponAttackSpeed = 0.5;
		_weaponLevel = Gold;
		break;
	}
}

void SlingShot::Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, float _playerDamageMod)
{
	_projectile = new Hudson::Entity::GameObject();
	_projectile->AddComponent(new Projectile(projectileDirection, spawnPos, CurrentScene, WT_SlingShot, _weaponAttackDamage* _playerDamageMod, _projectileMovementSpeed, _projectileRange));
	CurrentScene->AddObject(_projectile);
	std::cout << "Player Has Attacked With Slingshot" << "\n";

}
