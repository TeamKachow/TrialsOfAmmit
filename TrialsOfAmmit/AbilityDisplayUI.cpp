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
	_abilityFrameUI->SetName("WeaponUI");
	_abilityFrameUI->GetTransform().scale = (glm::vec2(64, 64));
	_currentPos = spawnPos;
	_abilityFrameUI->GetTransform().pos = spawnPos;

	_currentPlayer = _player;
}

AbilityDisplayUI::~AbilityDisplayUI()
{
}

void AbilityDisplayUI::OnCreate()
{
}

void AbilityDisplayUI::OnTick(const double& dt)
{
}

void AbilityDisplayUI::OnDestroy()
{
}

void AbilityDisplayUI::DrawPropertyUI()
{
}
