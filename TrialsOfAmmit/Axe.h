#pragma once
#include "BaseWeaponClass.h"

class Axe : public BaseWeaponClass
{
public:
	Hudson::Entity::GameObject* _slashAttack;
	Axe();
	~Axe();
	void Attack(facingDirections slashDirection, glm::vec2 playerPos, Hudson::World::Scene* currentScene) override;
};

