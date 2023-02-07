#include "Spear.h"

Spear::Spear()
{
	_weaponAttackDamage = 45;
	_weaponAttackSpeed = 0.75;
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
		_weaponAttackDamage = 45;
		_weaponAttackSpeed = 0.75;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 50;
		_weaponAttackSpeed = 0.7;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 55;
		_weaponAttackSpeed = 0.7;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 60;
		_weaponAttackSpeed = 0.7;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 65;
		_weaponAttackSpeed = 0.6;
		_weaponLevel = Gold;
		break;
	}

}
