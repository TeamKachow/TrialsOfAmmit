#pragma once
#include <Hudson.h>
#include "WeaponUpgrade.h"
#include "BaseWeaponClass.h"
#include "Axe.h"
#include "WeaponUpgrade.h"

class PickupWeapon : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PickupWeapon();
	~PickupWeapon();
	void RandomiseItem();
	BaseWeaponClass* _weaponPickup;
	WeaponUpgradeTypes _weaponLevel;

	Hudson::Entity::GameObject _weaponObject;
	Hudson::Render::SpriteComponent* _weaponSprite;
	Hudson::Physics::ColliderComponent* _weaponCollider;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

private:
	int _randomWeaponInt;
	int _randomRarityInt;
	


};

