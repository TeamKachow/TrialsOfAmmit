#pragma once
#include <Hudson.h>
#include "AbilityHolder.h"
#include "BaseAbilityClass.h"
#include "Stun.h"
#include "Roll.h"
#include "Rage.h"

class PickupAbilitys : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PickupAbilitys(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject);
	~PickupAbilitys();

	BaseAbilityClass* _abilityPickup;
		
	Hudson::Entity::GameObject* _abilityObject;
	Hudson::Render::SpriteComponent* _abilitySprite;
	Hudson::Physics::ColliderComponent* _abilityCollider;
	int _randomAbilityInt;
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};

