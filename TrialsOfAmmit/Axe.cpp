#include "Axe.h"

Axe::Axe()
{
	_weaponAttackDamage = 50;
	_weaponAttackSpeed = 1;
	_weaponLevel = Wood;
	UpgradeWeapon(_weaponLevel);
}

Axe::~Axe()
{
}

void Axe::UpgradeWeapon(WeaponUpgradeTypes CurrentWeaponLevel)
{
	switch (CurrentWeaponLevel)
	{
	case Wood: 
		_weaponAttackDamage = 50;
		_weaponAttackSpeed = 1;
		break;
	case Stone:
		_weaponAttackDamage = 60;
		_weaponAttackSpeed = 1;
		break;
	case Bronze:
		_weaponAttackDamage = 70;
		_weaponAttackSpeed = 0.9;
		break;
	case Iron:
		_weaponAttackDamage = 80;
		_weaponAttackSpeed = 0.8;
		break;
	case Gold:
		_weaponAttackDamage = 80;
		_weaponAttackSpeed = 0.7;
		break;
	}
	
}
