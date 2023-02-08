#pragma once
#include <Hudson.h>
#include "WeaponUpgrade.h"
#include "BaseWeaponClass.h"
#include "Axe.h"
#include "Khopesh.h"
#include "Bow.h"
#include "Spear.h"
#include "SlingShot.h"
#include "WeaponUpgrade.h"

class PickupWeapon : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	PickupWeapon(glm::vec2 spawnPos = {0,0});
	~PickupWeapon();
	void RandomiseItem();
	BaseWeaponClass* _weaponPickup;
	WeaponUpgradeTypes _weaponLevel;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	glm::vec2 _spawnPos;
	Hudson::Render::SpriteComponent* _weaponSprite;
	Hudson::Physics::ColliderComponent* _weaponCollider;


	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

private:
	int _randomWeaponInt;
	int _randomRarityInt;

	int _gridX;
	int _gridY;
	


};

