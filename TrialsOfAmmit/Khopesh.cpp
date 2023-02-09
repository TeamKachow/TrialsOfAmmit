#include "Khopesh.h"

Khopesh::Khopesh()
{
	_weaponAttackDamage = 35;
	_weaponAttackSpeed = 0.75;
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
		_weaponAttackDamage = 35;
		_weaponAttackSpeed = 0.75;
		_weaponLevel = Wood;
		break;
	case Stone:
		_weaponAttackDamage = 40;
		_weaponAttackSpeed = 0.75;
		_weaponLevel = Stone;
		break;
	case Bronze:
		_weaponAttackDamage = 45;
		_weaponAttackSpeed = 0.6;
		_weaponLevel = Bronze;
		break;
	case Iron:
		_weaponAttackDamage = 50;
		_weaponAttackSpeed = 0.6;
		_weaponLevel = Iron;
		break;
	case Gold:
		_weaponAttackDamage = 55;
		_weaponAttackSpeed = 0.5;
		_weaponLevel = Gold;
		break;
	}

}
