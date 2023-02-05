#pragma once
#include <Hudson.h>
#include "Roll.h"

class AbilityHolder : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	Roll* _roll;
	AbilityHolder();
	~AbilityHolder();
	float _timer;
	Hudson::Input::InputManager* _input;
	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

};
