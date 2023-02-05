#include "AbilityHolder.h"


AbilityHolder::AbilityHolder() : Behaviour ("Ability")
{
	_input = new Hudson::Input::InputManager;
}

AbilityHolder::~AbilityHolder()
{
}

void AbilityHolder::OnCreate()
{
	//_ability = _roll;
	_roll = new Roll;
}

void AbilityHolder::OnDestroy()
{
}

void AbilityHolder::DrawPropertyUI()
{

}

void AbilityHolder::OnTick(const double& dt)
{
	switch (state)
	{
	case ready:
		 
		//std::cout << "ability ready" << "\n";
		if (_input->getActionState("Ability"))
		{
			Hudson::World::Scene* _scene = _parent->GetScene();
			_roll->UseAbility(_scene, dt);
			 
			state = active;

			_activeTime = _roll->_activeTime;
			std::cout << "ability active for : " << _activeTime << " seconds" << "\n";
		}
		break;
	case active:

		if (_activeTime > 0)
		{
			std::cout << "ability active" << "\n";
			_activeTime -= dt;
		}
		else
		{
			std::cout << "ability inactive" << "\n";

			state = cooldown;
			
			_cooldownTime = _roll->_cooldownTime;
			std::cout << "ability on cooldown for : " << _cooldownTime << " seconds" << "\n";
		}
		
		break;
	case cooldown:
		
		if (_cooldownTime > 0)
		{
			std::cout << "ability on cooldown" << "\n";
			_cooldownTime -= dt;
		}
		else
		{
			std::cout << "ability ready" << "\n";
			state = ready;
		}
	}
}

//void AbilityHolder::OnDestroy()
//{
//
//}

//void AbilityHolder::DrawPropertyUI()
//{
//}
