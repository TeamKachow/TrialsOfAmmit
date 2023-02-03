#include "SlingShot.h"

SlingShot::SlingShot()
{
	_weaponAttackDamage = 10.0;
	_projectileMovementSpeed = 250;
	_projectileRange = 2.0;
	_weaponAttackSpeed = 0.75;
}

SlingShot::~SlingShot()
{
}

void SlingShot::Attack(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene)
{
	_projectile = new Hudson::Entity::GameObject();
	_projectile->AddComponent(new Projectile(projectileDirection, spawnPos, CurrentScene, _projectile, WT_SlingShot, _weaponAttackDamage, _projectileMovementSpeed, _projectileRange));
	std::cout << "Player Has Attacked With Slingshot" << "\n";

}
