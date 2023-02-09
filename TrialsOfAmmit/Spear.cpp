#include "Spear.h"

Spear::Spear()
{
	_weaponAttackDamage = 20;
	_weaponAttackSpeed = 0.5;
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
		_weaponAttackDamage = 20;
		_weaponAttackSpeed = 0.5;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 25;
		_weaponAttackSpeed = 0.5;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 35;
		_weaponAttackSpeed = 0.4;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 40;
		_weaponAttackSpeed = 0.4;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 45;
		_weaponAttackSpeed = 0.4;
		_weaponLevel = Gold;
		break;
	}

}
