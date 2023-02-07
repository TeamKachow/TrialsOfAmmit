#include "Spear.h"

Spear::Spear()
{
	_weaponAttackDamage = 35;
	_weaponAttackSpeed = 1;
	_weaponLevel = Wood;
	_weaponType = WT_Spear;
}

Spear::~Spear()
{
}

void Spear::UpgradeWeapon(WeaponUpgradeTypes CurrentWeaponLevel)
{
	switch (CurrentWeaponLevel)
	{
	case Wood:
		_weaponAttackDamage = 35;
		_weaponAttackSpeed = 1;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 45;
		_weaponAttackSpeed = 1.1;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 55;
		_weaponAttackSpeed = 1.15;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 65;
		_weaponAttackSpeed = 1.2;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 75;
		_weaponAttackSpeed = 1.25;
		_weaponLevel = Gold;
		break;
	}

}
