#include "Chest.h"
#include "PickupWeapon.h"

Chest::Chest(glm::vec2 spawnPos) : Behaviour("Chest")
{
	_spawnPos = spawnPos;
	_isOpen = false;
}

Chest::~Chest()
{
}

void Chest::OnInteract()
{
	if (_isOpen == false)
	{
		_spawnPos = _parent->GetTransform().pos;
		_chestSprite->SetGridPos(glm::vec2(1, 1));
		Hudson::Entity::GameObject* WeaponPickup = new Hudson::Entity::GameObject();
		WeaponPickup->AddComponent(new PickupWeapon(glm::vec2(_spawnPos.x, _spawnPos.y + 75)));
		_parent->GetScene()->AddObject(WeaponPickup);
		_isOpen = true;
	}
}

void Chest::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_chestSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Chest"));
	_chestSprite->SetGridSize(glm::vec2(2, 1));
	_chestSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_chestCollider = new Hudson::Physics::ColliderComponent();
	_chestSprite->SetGridPos(glm::vec2(0, 1));
	_chestSprite->SetDepthOrder(1);
	_parent->AddComponent(_chestSprite);
	_parent->AddComponent(_chestCollider);
	_parent->SetName("Chest");
	_parent->GetTransform().pos = _spawnPos;
}

void Chest::OnTick(const double& dt)
{
}

void Chest::OnDestroy()
{
}

void Chest::DrawPropertyUI()
{
}

void Chest::FromJson(const nlohmann::json& j)
{
}

void Chest::ToJson(nlohmann::json& j)
{
}
