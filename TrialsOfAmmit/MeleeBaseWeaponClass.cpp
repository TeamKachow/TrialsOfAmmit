#include "MeleeBaseWeaponClass.h"
#include "MeleeAttack.h"
#include "MeleeCollider.h"

void MeleeBaseWeaponClass::Attack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene)
{
	std::cout << _weaponAttackDamage << "\n";

	_slashAttack = new Hudson::Entity::GameObject();
	_slashAttack->AddComponent(new MeleeAttack(slashDirection, playerPos, currentScene, _slashAttack));

	_slashCollider = new Hudson::Entity::GameObject();
	_slashCollider->AddComponent(new MeleeCollider(slashDirection, playerPos, currentScene, _slashCollider, _weaponAttackDamage));
}
