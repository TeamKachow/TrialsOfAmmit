#include "Axe.h"

Axe::Axe()
{
	_weaponAttackDamage = 10;
	_weaponAttackSpeed = 1;
	_weaponName = "Axe";
}

Axe::~Axe()
{
}

//void Axe::Attack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene)
//{
//	/*_slashAttack = new Hudson::Entity::GameObject();
//	_slashAttack->AddComponent(new MeleeAttack(slashDirection, playerPos, currentScene, _slashAttack));
//
//	_slashCollider = new Hudson::Entity::GameObject();
//	_slashCollider->AddComponent(new MeleeCollider(slashDirection, playerPos, currentScene, _slashCollider));*/
//}
