#include "Khopesh.h"

Khopesh::Khopesh()
{
	_weaponAttackDamage = 35;
	_weaponAttackSpeed = 0.5;
}

Khopesh::~Khopesh()
{

}

void Khopesh::UpgradeWeapon(WeaponUpgradeTypes CurrentWeaponLevel)
{
	switch (CurrentWeaponLevel)
	{
	case Wood:
		_weaponAttackDamage = 35;
		_weaponAttackSpeed = 0.5;
		break;
	case Stone:
		_weaponAttackDamage = 40;
		_weaponAttackSpeed = 0.4;
		break;
	case Bronze:
		_weaponAttackDamage = 45;
		_weaponAttackSpeed = 0.4;
		break;
	case Iron:
		_weaponAttackDamage = 50;
		_weaponAttackSpeed = 0.4;
		break;
	case Gold:
		_weaponAttackDamage = 55;
		_weaponAttackSpeed = 0.4;
		break;
	}

}
