#include "AbilityDisplayUI.h"

AbilityDisplayUI::AbilityDisplayUI(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject, Hudson::World::Scene* _Scene, Player* _player) : Behaviour ("AbilityUI")
{
	_abilityFrameUI = _refObject;
	_currentScene = _Scene;
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_abilityFrameUISprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("UIFrame"));
	_abilityFrameUISprite->SetSize(glm::vec2(16.0f, 16.0f));
	_abilityFrameUISprite->SetGridSize(glm::vec2(1, 1));
	_abilityFrameUISprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_abilityFrameUI->AddComponent(_abilityFrameUISprite);
	_abilityFrameUI->SetName("AbilityUIFrame");
	_abilityFrameUI->GetTransform().scale = (glm::vec2(64, 64));
	_abilityFrameUISprite->SetDepthOrder(1);
	_currentPos = spawnPos;
	_abilityFrameUI->GetTransform().pos = spawnPos;

	_currentPlayer = _player;
}

AbilityDisplayUI::~AbilityDisplayUI()
{
}

void AbilityDisplayUI::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	Hudson::Entity::GameObject* AbilityUISprite = new Hudson::Entity::GameObject();
	_abilitySprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Abilitys"));
	//_abilitySprite->SetSize(glm::vec2(16.0f, 16.0f));
	_abilitySprite->SetGridSize(glm::vec2(2, 1));
	_abilitySprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_abilitySprite->SetGridPos(glm::vec2(0, 1));
	_abilitySprite->SetDepthOrder(2);
	AbilityUISprite->SetName("AbilityUIIcon");
	AbilityUISprite->GetTransform().pos = _currentPos;
	AbilityUISprite->GetTransform().scale = (glm::vec2(64, 64));
	AbilityUISprite->AddComponent(_abilitySprite);
	_currentScene->AddObject(AbilityUISprite);	
}

void AbilityDisplayUI::OnTick(const double& dt)
{
	if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_ROLL)
	{
		_abilitySprite->SetGridPos(glm::vec2(0, 1));
	}
	if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_STUN)
	{
		_abilitySprite->SetGridPos(glm::vec2(1, 1));
	}
}

void AbilityDisplayUI::OnDestroy()
{
}

void AbilityDisplayUI::DrawPropertyUI()
{
}
