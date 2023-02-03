#include "Spear.h"

Spear::Spear()
{
	_weaponAttackDamage = 45;
	_weaponAttackSpeed = 0.75;
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
		break;
	case Stone:
		_weaponAttackDamage = 50;
		_weaponAttackSpeed = 0.7;
		break;
	case Bronze:
		_weaponAttackDamage = 55;
		_weaponAttackSpeed = 0.7;
		break;
	case Iron:
		_weaponAttackDamage = 60;
		_weaponAttackSpeed = 0.7;
		break;
	case Gold:
		_weaponAttackDamage = 65;
		_weaponAttackSpeed = 0.6;
		break;
	}

}
