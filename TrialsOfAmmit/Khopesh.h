#pragma once
#include "MeleeBaseWeaponClass.h"

class Khopesh : public MeleeBaseWeaponClass
{
public:
	Khopesh();
	~Khopesh();
	void UpgradeWeapon(WeaponUpgradeTypes Level) override;
};

