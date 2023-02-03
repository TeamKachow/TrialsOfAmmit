#pragma once
#include "MeleeBaseWeaponClass.h"

class Axe : public MeleeBaseWeaponClass
{
public:
	Axe();
	~Axe();
	void UpgradeWeapon(WeaponUpgradeTypes Level) override;
};

