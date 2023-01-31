#include "Axe.h"
#include "MeleeAttack.h"

Axe::Axe()
{
	_weaponAttackDamage = 5.0;
	_weaponAttackSpeed = 0.5;
	_weaponName = "Axe";
}

Axe::~Axe()
{
}

void Axe::Attack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene)
{
	_slashAttack = new Hudson::Entity::GameObject();
	_slashAttack->AddComponent(new MeleeAttack(slashDirection, playerPos, currentScene, _slashAttack));
}
