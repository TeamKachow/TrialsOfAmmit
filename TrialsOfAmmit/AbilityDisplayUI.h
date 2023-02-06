#pragma once
#include <Hudson.h>
#include "AbilityHolder.h"
#include "Player.h"
#include "BaseAbilityClass.h"
#include "Roll.h"
class AbilityDisplayUI : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public: 
	AbilityDisplayUI(glm::vec2 spawnPos, Hudson::Entity::GameObject* _refObject, Hudson::World::Scene* _Scene, Player* _player);
	~AbilityDisplayUI();

	Hudson::Entity::GameObject* _abilityFrameUI;
	Hudson::Render::SpriteComponent* _abilityFrameUISprite;
	Hudson::Render::SpriteComponent* _frameSprite;
	Hudson::World::Scene* _currentScene;
	Hudson::Render::SpriteComponent* _abilitySprite;
	Player* _currentPlayer;
	glm::uvec2 _currentPos;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};

