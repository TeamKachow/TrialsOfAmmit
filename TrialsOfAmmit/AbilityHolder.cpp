#include "AbilityHolder.h"


AbilityHolder::AbilityHolder() : Behaviour ("Ability")
{
	_input = new Hudson::Input::InputManager;
	_timer = 0;
	_roll = new Roll;
	_stun = new Stun;
	_currentAbility = _stun;
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
	if (_currentAbility->_abilityState == ready)
	{
		if (_input->getActionState("Ability")) //Key Checks
		{

			_currentAbility->UseAbility(_parent->GetScene());

		}
	}
	if (_currentAbility->_abilityState == active)
	{
		_timer += dt;
		if (_timer >= _currentAbility->_abilityActiveTime)
		{
			_currentAbility->DeactiveAbility(_parent->GetScene());
			_timer = 0;
	
			
		}
	}
	if (_currentAbility->_abilityState == cooldown)
	{
		_timer += dt;
		if (_timer >= _currentAbility->_abilityCoolDownTime)
		{
			_currentAbility->_abilityState = ready;
			_timer = 0;


		}
	}
}