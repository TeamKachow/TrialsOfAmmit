#pragma once
#include "BaseAbilityClass.h"
#include "AiAgent.h"

class RoomAOE : public BaseAbilityClass
{
public:
	RoomAOE();
	~RoomAOE();
	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)override;

	AiAgent* _agent;
	float _aoeDamage;
	float _enemyCurrentHealth;
};

