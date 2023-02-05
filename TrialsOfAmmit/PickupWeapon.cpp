#include "PickupWeapon.h"
#include <random>

using namespace std;

PickupWeapon::PickupWeapon() : Behaviour("WeaponPickUp")
{
	_randomRarityInt = 0;
	_randomRarityInt = 0;
	RandomiseItem();
}

PickupWeapon::~PickupWeapon()
{
}

void PickupWeapon::RandomiseItem()
{
	random_device rand;
	uniform_int_distribution<int> dist(0, 4);
	_randomWeaponInt = dist(rand);
	if (_randomWeaponInt == 0)
	{
		_weaponPickup = new Axe;
		//Axe
	}
	else if (_randomWeaponInt == 1)
	{

		//Khopesh
	}
	else if (_randomWeaponInt == 2)
	{
		//Spear
	}
	else if (_randomWeaponInt == 3)
	{
		//Bow
	}
	else if (_randomWeaponInt == 4)
	{
		//Slingshot
	}

	_randomRarityInt = dist(rand);
	if (_randomWeaponInt == 0)
	{
		_weaponLevel = Wood;
	}
	else if (_randomWeaponInt == 1)
	{
		_weaponLevel = Stone;
	}
	else if (_randomWeaponInt == 2)
	{
		_weaponLevel = Bronze;
	}
	else if (_randomWeaponInt == 3)
	{
		_weaponLevel = Iron;
	}
	else if (_randomWeaponInt == 4)
	{
		_weaponLevel = Gold;
	}
	std::cout << _weaponLevel << "\n";
	std::cout << _randomWeaponInt << "\n";


}

void PickupWeapon::OnCreate()
{
	
}

void PickupWeapon::OnTick(const double& dt)
{
	_parent->GetTransform().scale = glm::vec2(50, 50);
}

void PickupWeapon::OnDestroy()
{
}

void PickupWeapon::DrawPropertyUI()
{
}
