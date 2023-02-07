#include "MeleeBaseWeaponClass.h"
#include "MeleeAttack.h"
#include "MeleeCollider.h"

void MeleeBaseWeaponClass::Attack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene)
{
	std::cout << _weaponAttackDamage << "\n";

	_slashAttack = new Hudson::Entity::GameObject();
	_slashAttack->AddComponent(new MeleeAttack(slashDirection, playerPos, currentScene));
	currentScene->AddObject(_slashAttack);

	_slashCollider = new Hudson::Entity::GameObject();
	_slashCollider->AddComponent(new MeleeCollider(slashDirection, playerPos, currentScene, _weaponAttackDamage, false));
	currentScene->AddObject(_slashCollider);
}

void MeleeBaseWeaponClass::AiAttack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene)
{
	std::cout << _weaponAttackDamage << "\n";

	_slashAttack = new Hudson::Entity::GameObject();
	_slashAttack->AddComponent(new MeleeAttack(slashDirection, playerPos, currentScene));
	currentScene->AddObject(_slashAttack);

	_slashCollider = new Hudson::Entity::GameObject();
	_slashCollider->AddComponent(new MeleeCollider(slashDirection, playerPos, currentScene, _weaponAttackDamage, true));
	currentScene->AddObject(_slashCollider);
}
