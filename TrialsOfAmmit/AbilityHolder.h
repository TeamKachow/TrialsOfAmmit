#pragma once
#include <Hudson.h>
#include "BaseAbilityClass.h"
#include "Roll.h"
#include "Stun.h"

class AbilityHolder : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	BaseAbilityClass* _currentAbility;
	Roll* _roll;
	Stun* _stun;

	AbilityHolder();
	~AbilityHolder();
	float _timer;
	Hudson::Input::InputManager* _input;
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

};
