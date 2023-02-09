#pragma once
#include <Hudson.h>
#include "BaseWeaponClass.h"
#include "Player.h"
#include "SlingShot.h"
#include "Bow.h"
#include "Spear.h"
#include "Axe.h"
#include "Khopesh.h"
class WeaponDisplayUI : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	//WeaponDisplayUI(glm::vec2 spawnPos, Hudson::World::Scene* _scene, Player* _player);
	WeaponDisplayUI(glm::vec2 spawnPos = { 1450.0f, 25.0f }, Hudson::World::Scene* _scene = nullptr, Player* _player = nullptr);
	~WeaponDisplayUI();

	Hudson::Entity::GameObject* _weaponUI;
	Hudson::Render::SpriteComponent* _weaponUISprite;
	Hudson::Render::SpriteComponent* _weaponSprite;
	Hudson::World::Scene* _currentScene;


	BaseWeaponClass* _currentWeapon;
	Player* _currentPlayer;

	glm::uvec2 _currentPos;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;

	int _gridX;
	int _gridY;
};

