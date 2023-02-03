#include "BaseWeaponClass.h"

#include <iostream>

BaseWeaponClass::BaseWeaponClass()
{
}

BaseWeaponClass::~BaseWeaponClass()
{
}

void BaseWeaponClass::Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene)
{
	std::cout << "Player Has Attacked" << "\n";
}

void BaseWeaponClass::AiAttack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene)
{
	std::cout << "AI Has Attacked" << "\n";
}

void BaseWeaponClass::UpgradeWeapon(WeaponUpgradeTypes Level)
{
}



