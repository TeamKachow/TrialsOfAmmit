#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <Hudson.h>
#include "abilityTargets.h"
#include "AbilityStates.h"
#include "Player.h"
#include "AbilityType.h"

class BaseAbilityClass
{
public:
	AbilityTypes _abilityType;
	BaseAbilityClass();
	~BaseAbilityClass();
	virtual void UseAbility(Hudson::World::Scene* _CurrentPassScene);
	virtual void DeactiveAbility(Hudson::World::Scene* _CurrentPassScene);
	float _abilityActiveTime;
	float _abilityCoolDownTime;
	AbilityState _abilityState;

protected:


private:
	
};





