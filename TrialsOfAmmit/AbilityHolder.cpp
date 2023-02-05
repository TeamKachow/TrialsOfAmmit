#include "AbilityHolder.h"


AbilityHolder::AbilityHolder() : Behaviour ("Ability")
{
	_input = new Hudson::Input::InputManager;
	_timer = 0;
	_roll = new Roll;
}

AbilityHolder::~AbilityHolder()
{
}

void AbilityHolder::OnCreate()
{
}

void AbilityHolder::OnDestroy()
{
}

void AbilityHolder::DrawPropertyUI()
{

}

void AbilityHolder::OnTick(const double& dt)
{
	if (_roll->_abilityState == ready)
	{
		if (_input->getActionState("Ability")) //Key Checks
		{

			_roll->UseAbility(_parent->GetScene(), dt);

		}
	}
	if (_roll->_abilityState == active)
	{
		_timer += dt;
		if (_timer >= _roll->_abilityActiveTime)
		{
			_roll->DeactiveAbility(_parent->GetScene(), dt);
			_timer = 0;
	
			
		}
	}
	if (_roll->_abilityState == cooldown)
	{
		_timer += dt;
		if (_timer >= _roll->_abilityCoolDownTime)
		{
			_roll->_abilityState = ready;
			_timer = 0;


		}
	}
}