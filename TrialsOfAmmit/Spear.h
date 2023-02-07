#pragma once
#include "MeleeBaseWeaponClass.h"
class Spear : public MeleeBaseWeaponClass
{
public:
	Spear();
	~Spear();
	void UpgradeWeapon(WeaponUpgradeTypes Level) override;
};

