#include "PickupWeapon.h"
#include <random>

using namespace std;



PickupWeapon::PickupWeapon(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject) : Behaviour("WeaponPickUp")
{
	_weaponObject = _refObject;
	_weaponCollider = new Hudson::Physics::ColliderComponent();
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_weaponSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Weapon"));
	_weaponSprite->SetSize(glm::vec2(16.0f, 16.0f));
	_weaponSprite->SetGridSize(glm::vec2(5, 5));
	_weaponSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_weaponObject->AddComponent(_weaponSprite);
	_weaponObject->AddComponent(_weaponCollider);
	_weaponObject->SetName("WeaponPickup");

	_weaponObject->GetTransform().pos = spawnPos;

	_gridX = 0;
	_gridY = 0;

	_randomRarityInt = 0;
	_randomRarityInt = 0;
	RandomiseItem();
}

PickupWeapon::~PickupWeapon()
{
}

void PickupWeapon::RandomiseItem()
{
	random_device rand;
	uniform_int_distribution<int> dist(0, 4);
	_randomWeaponInt = dist(rand);
	if (_randomWeaponInt == 0)
	{
		_weaponPickup = new Axe;
		_gridX = _randomWeaponInt;
	}
	else if (_randomWeaponInt == 1)
	{
		_weaponPickup = new Khopesh;
		_gridX = _randomWeaponInt;
	}
	else if (_randomWeaponInt == 2)
	{
		_weaponPickup = new Spear;
		_gridX = _randomWeaponInt;
	}
	else if (_randomWeaponInt == 3)
	{
		_weaponPickup = new Bow;
		_gridX = _randomWeaponInt;
	}
	else if (_randomWeaponInt == 4)
	{
		_weaponPickup = new SlingShot;
		_gridX = _randomWeaponInt;
	}

	_randomRarityInt = dist(rand);
	if (_randomRarityInt == 0)
	{
		_gridY = _randomRarityInt;
		_weaponLevel = Wood;
	}
	else if (_randomRarityInt == 1)
	{
		_gridY = _randomRarityInt;
		_weaponLevel = Stone;
	}
	else if (_randomRarityInt == 2)
	{
		_gridY = _randomRarityInt;
		_weaponLevel = Bronze;
	}
	else if (_randomRarityInt == 3)
	{
		_gridY = _randomRarityInt;
		_weaponLevel = Iron;
	}
	else if (_randomRarityInt == 4)
	{
		_gridY = _randomRarityInt;
		_weaponLevel = Gold;
	}
	_weaponSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	_weaponPickup->UpgradeWeapon(_weaponLevel);
	std::cout << _weaponLevel << "\n";
	std::cout << _randomWeaponInt << "\n";


}

void PickupWeapon::OnCreate()
{
	_parent->GetTransform().scale = glm::vec2(48, 48);
}

void PickupWeapon::OnTick(const double& dt)
{
	
}

void PickupWeapon::OnDestroy()
{
}

void PickupWeapon::DrawPropertyUI()
{
}