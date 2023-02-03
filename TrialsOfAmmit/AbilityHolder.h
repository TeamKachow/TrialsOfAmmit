#pragma once

///
/// This is attached to the player
/// 
#include <Hudson.h>
#include "BaseAbilityClass.h"
#include "Roll.h"
enum AbilityState
{
	ready,
	active,
	cooldown
};
class AbilityHolder : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	AbilityHolder();
	~AbilityHolder();
	//BaseAbilityClass* _ability;
	
	float _cooldownTime;
	float _activeTime;
	AbilityState state = ready;
	Hudson::Input::InputManager* _input;
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
	
	// List of Abilities here
	Roll* _roll;


private:
};
