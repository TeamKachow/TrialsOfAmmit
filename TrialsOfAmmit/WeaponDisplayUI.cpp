#include "WeaponDisplayUI.h"


WeaponDisplayUI::WeaponDisplayUI(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject, Hudson::World::Scene* _Scene, Player* _player) : Behaviour("WeaponUIDisplay")
{
	_weaponUI = _refObject;
	_currentScene = _Scene;
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_weaponUISprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("UIFrame"));
	_weaponUISprite->SetSize(glm::vec2(16.0f, 16.0f));
	_weaponUISprite->SetGridSize(glm::vec2(1, 1));
	_weaponUISprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_weaponUI->AddComponent(_weaponUISprite);
	_weaponUI->SetName("WeaponUI");
	_weaponUI->GetTransform().scale = (glm::vec2(128, 128));
	_currentPos = spawnPos;
	_weaponUI->GetTransform().pos = spawnPos;
	_gridX = 0;
	_gridY = 0;

	_currentPlayer = _player;
}

WeaponDisplayUI::~WeaponDisplayUI()
{
}

void WeaponDisplayUI::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	Hudson::Entity::GameObject* WeaponUISprite = new Hudson::Entity::GameObject();

	_weaponSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Weapon"));
	_weaponSprite->SetSize(glm::vec2(16.0f, 16.0f));
	_weaponSprite->SetGridSize(glm::vec2(5, 5));
	_weaponSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_weaponSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	WeaponUISprite->GetTransform().pos = _currentPos;
	WeaponUISprite->GetTransform().scale = (glm::vec2(128, 128));
	WeaponUISprite->AddComponent(_weaponSprite);
	_currentScene->AddObject(WeaponUISprite);

	
	
}

void WeaponDisplayUI::OnTick(const double& dt)
{
	_currentWeapon = _currentPlayer->_playersWeapon;
	switch (_currentWeapon->_weaponType)
	{
	case WT_Axe:
		_gridX = 0;
		break;
	case WT_Khopesh:
		_gridX = 1;
		break;
	case WT_Spear:
		_gridX = 2;
		break;
	case WT_Bow:
		_gridX = 3;
		break;
	case WT_SlingShot:
		_gridX = 4;
		break;
	}
	//std::cout << _currentWeapon->_weaponLevel << "\n";
	switch (_currentWeapon->_weaponLevel)
	{
	case Wood:
		_gridY = 0;
		break;
	case Stone:
		_gridY = 1;
		break;
	case Bronze:
		_gridY = 2;
		break;
	case Iron:
		_gridY = 3;
		break;
	case Gold:
		_gridY = 4;
		break;
	}
	_weaponSprite->SetGridPos(glm::vec2(_gridX, _gridY));
}

void WeaponDisplayUI::OnDestroy()
{
}

void WeaponDisplayUI::DrawPropertyUI()
{
}
