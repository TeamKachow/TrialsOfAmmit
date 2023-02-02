#pragma once

#include "BaseAbilityClass.h"

class Roll : public BaseAbilityClass
{
public:
	Roll();
	~Roll();

	float _rollSpeed;

	void UseAbility() override;
private:
};

