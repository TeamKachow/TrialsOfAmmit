#pragma once
#include "BaseAbilityClass.h"
#include "AiAgent.h"

class Stun : public BaseAbilityClass
{
public:
	Stun();
	~Stun();
	AiAgent* _agent;
	void UseAbility(Hudson::World::Scene* _CurrentPassScene) override;
	void DeactivateAbility(Hudson::World::Scene* _CurrentPassScene)override;
};

