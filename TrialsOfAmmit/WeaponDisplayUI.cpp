#include "WeaponDisplayUI.h"


WeaponDisplayUI::WeaponDisplayUI(glm::vec2 spawnPos, Hudson::World::Scene* _Scene, Player* _player) : Behaviour("WeaponUIDisplay")
{
	//_weaponUI = _refObject;
	_currentScene = _Scene;
	_currentPos = spawnPos;
	_currentPlayer = _player;

	_gridX = 0;
	_gridY = 0;

}

WeaponDisplayUI::~WeaponDisplayUI()
{
}

void WeaponDisplayUI::OnCreate()
{
	//Makes the Frame
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_weaponUISprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("UIFrame"));
	_weaponUISprite->SetGridSize(glm::vec2(1, 1));
	_weaponUISprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_weaponUISprite->SetDepthOrder(1);
	_parent->AddComponent(_weaponUISprite);
	_parent->SetName("WeaponUIFrame");
	_parent->GetTransform().scale = (glm::vec2(64, 64));
	
	_parent->GetTransform().pos = _currentPos;


	//Makes the Weapon Icon
	Hudson::Entity::GameObject* WeaponUISprite = new Hudson::Entity::GameObject();
	_weaponSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Weapon"));
	_weaponSprite->SetGridSize(glm::vec2(5, 5));
	_weaponSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_weaponSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	_weaponSprite->SetDepthOrder(2);
	WeaponUISprite->SetName("WeaponUIIcon");
	WeaponUISprite->GetTransform().pos = _currentPos;
	WeaponUISprite->GetTransform().scale = (glm::vec2(64, 64));
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
