#include "Khopesh.h"

Khopesh::Khopesh()
{
	_weaponAttackDamage = 20;
	_weaponAttackSpeed = 1;
	_weaponLevel = Wood;
	_weaponType = WT_Khopesh;
}

Khopesh::~Khopesh()
{

}

void Khopesh::UpgradeWeapon(WeaponUpgradeTypes CurrentWeaponLevel)
{
	switch (CurrentWeaponLevel)
	{
	case Wood:
		_weaponAttackDamage = 20;
		_weaponAttackSpeed = 1;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 25;
		_weaponAttackSpeed = 1;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 30;
		_weaponAttackSpeed = 1.1;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 35;
		_weaponAttackSpeed = 1.2;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 45;
		_weaponAttackSpeed = 1.25;
		_weaponLevel = Gold;
		break;
	}

}
