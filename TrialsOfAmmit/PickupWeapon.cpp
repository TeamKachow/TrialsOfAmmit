#include "PickupWeapon.h"
#include <random>

using namespace std;



PickupWeapon::PickupWeapon(glm::vec2 spawnPos) : Behaviour("WeaponPickUp")
{

	_gridX = 0;
	_gridY = 0;
	_spawnPos = spawnPos;

	_randomRarityInt = 0;
	_randomRarityInt = 0;

}

PickupWeapon::~PickupWeapon()
{
}

void PickupWeapon::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_weaponSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Weapon"));
	_weaponSprite->SetGridSize(glm::vec2(5, 5));
	_weaponSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_weaponSprite->SetDepthOrder(1);
	_weaponCollider = new Hudson::Physics::ColliderComponent();

	_parent->AddComponent(_weaponSprite);
	_parent->AddComponent(_weaponCollider);
	_parent->SetName("WeaponPickup");
	_parent->GetTransform().pos = _spawnPos;
	_parent->GetTransform().scale = glm::vec2(48, 48);
	

	RandomiseItem();
	
}

void PickupWeapon::RandomiseItem()
{
	random_device rand;
	uniform_int_distribution<int> dist(0, 4);
	_randomWeaponInt = dist(rand);
	if (_randomWeaponInt == 0)
	{
		_weaponPickup = new Axe;
		_gridX = 0;
	}
	else if (_randomWeaponInt == 1)
	{
		_weaponPickup = new Khopesh;
		_gridX = 1;
	}
	else if (_randomWeaponInt == 2)
	{
		_weaponPickup = new Spear;
		_gridX = 2;
	}
	else if (_randomWeaponInt == 3)
	{
		_weaponPickup = new Bow;
		_gridX = 3;
	}
	else if (_randomWeaponInt == 4)
	{
		_weaponPickup = new SlingShot;
		_gridX = 4;
	}
	random_device random;
	uniform_int_distribution<int> dists(0, 100);
	_randomRarityInt = dists(random);

	if (_randomRarityInt >= 0 && _randomRarityInt <= 35)
	{
		_gridY = 0;
		_weaponLevel = Wood;
	}
	else if (_randomRarityInt >= 36 && _randomRarityInt <= 65)
	{
		_gridY = 1;
		_weaponLevel = Stone;
	}
	else if (_randomRarityInt >= 66 && _randomRarityInt <= 80)
	{
		_gridY = 2;
		_weaponLevel = Bronze;
	}
	else if (_randomRarityInt >= 81 && _randomRarityInt <= 92)
	{
		_gridY = 3;
		_weaponLevel = Iron;
	}
	else if (_randomRarityInt >= 92 && _randomRarityInt <= 100)
	{
		_gridY = 4;
		_weaponLevel = Gold;
	}
	_weaponSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	_weaponPickup->UpgradeWeapon(_weaponLevel);

}

void PickupWeapon::FromJson(const nlohmann::json& j)
{
}

void PickupWeapon::ToJson(nlohmann::json& j)
{
}



void PickupWeapon::OnTick(const double& dt)
{
	
}

void PickupWeapon::OnDestroy()
{
}

void PickupWeapon::DrawPropertyUI()
{
	if (ImGui::Button("Reshuffle"))
	{
		RandomiseItem();
	}
}
