#include "AbilityHolder.h"


AbilityHolder::AbilityHolder() : Behaviour ("Ability")
{
	_input = new Hudson::Input::InputManager;
	_timer = 0;
	_roll = new Roll;
	_stun = new Stun;
	_rage = new Rage;
	_heal = new Heal;
	_roomaoe = new RoomAOE;
	_currentAbility = _roll;
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

void AbilityHolder::FromJson(const nlohmann::json& j)
{
}

void AbilityHolder::ToJson(nlohmann::json& j)
{
}

void AbilityHolder::OnTick(const double& dt) // need to make so that it can't be used if player is dead
{
	if (_currentAbility->_abilityState == ready)
	{
		if (_input->getActionState("Ability")) //Key Checks --- Currently been made to E in game
		{
			_currentAbility->UseAbility(_parent->GetScene());
		}
	}
	if (_currentAbility->_abilityState == active)
	{
		_timer += dt;
		if (_timer >= _currentAbility->_abilityActiveTime)
		{
			_currentAbility->DeactivateAbility(_parent->GetScene());
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
	// * polish --- Switch Statement??? i mean.... its works so this is something AFTER.
}