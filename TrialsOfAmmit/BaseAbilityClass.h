#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <Hudson.h>
#include "abilityTargets.h"
#include "AbilityStates.h"
#include "Player.h"

class BaseAbilityClass
{
public:
	BaseAbilityClass();
	~BaseAbilityClass();
	virtual void UseAbility(Hudson::World::Scene* _CurrentPassScene);
	float _abilityActiveTime;
	float _abilityCoolDownTime;
	AbilityState _abilityState;

protected:


private:
	
};





