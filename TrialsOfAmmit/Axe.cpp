#include "Axe.h"

Axe::Axe()
{
	_weaponAttackDamage = 50;
	_weaponAttackSpeed = 1;
	_weaponLevel = Wood;
	_weaponType = WT_Axe;
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
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 60;
		_weaponAttackSpeed = 1;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 70;
		_weaponAttackSpeed = 0.9;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 80;
		_weaponAttackSpeed = 0.8;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 80;
		_weaponAttackSpeed = 0.7;
		_weaponLevel = Gold;
		break;
	}
	
}
