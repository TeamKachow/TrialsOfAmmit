#pragma once
#include "BaseWeaponClass.h"
class MeleeBaseWeaponClass : public BaseWeaponClass
{
	Hudson::Entity::GameObject* _slashAttack;
	Hudson::Entity::GameObject* _slashCollider;

	void Attack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene) override;
};

