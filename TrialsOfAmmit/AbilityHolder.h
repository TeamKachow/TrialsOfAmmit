#pragma once

///
/// This is attached to the player
/// 
#include <Hudson.h>
#include "BaseAbilityClass.h"

class AbilityHolder : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	BaseAbilityClass* _ability;
	float _cooldownTime;
	float _activeTime;

	enum AbilityState
	{
		ready,
		active,
		cooldown
	};

	//default state is ready
	AbilityState state = ready;

	char input; // ideally input function

	void OnCreate()
	{

	}
	
	void OnTick(const double& dt)
	{
		switch (state)
		{
		case AbilityHolder::ready:
			if (input == 'a') // if key is pressed.
			{
				_ability->UseAbility();
				state = active;
				_activeTime = _ability->_activeTime;
			}
			break;
		case AbilityHolder::active:
			if (_activeTime > 0)
			{
				_activeTime -= dt;
			}
			else
			{
				state = cooldown;
				_cooldownTime = _ability->_cooldownTime;
			}
			break;
		case AbilityHolder::cooldown:
			if (_cooldownTime > 0)
			{
				_cooldownTime -= dt;
			}
			else
			{
				state = ready;
			}
			break;
		}
	}
	
	void OnDestroy()
	{

	}
	
	void DrawPropertyUI()
	{

	}
};
