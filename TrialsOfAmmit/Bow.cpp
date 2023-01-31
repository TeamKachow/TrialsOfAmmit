#include "Bow.h"

#include <iostream>

Bow::Bow()
{
	_weaponAttackDamage = 20.0;
	_weaponAttackSpeed = 0.5;
	_weaponName = "Bow";
}

Bow::~Bow()
{
}

void Bow::Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene)
{
	_projectile = new Hudson::Entity::GameObject();
	_projectile->AddComponent(new Projectile(projectileDirection, spawnPos, CurrentScene, _projectile));
	std::cout << "Player Has Attacked With Bow" << "\n";
}

