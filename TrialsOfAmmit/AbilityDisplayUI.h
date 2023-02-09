#pragma once
#include <Hudson.h>
#include "AbilityHolder.h"
#include "Player.h"
#include "BaseAbilityClass.h"
#include "Roll.h"
class AbilityDisplayUI : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public: 
	//AbilityDisplayUI(glm::vec2 spawnPos, Hudson::World::Scene* _Scene, Player* _player);
	AbilityDisplayUI(glm::vec2 spawnPos = { 1250.0f, 25.0f }, Hudson::World::Scene* _scene = nullptr, Player* _player = nullptr);
	~AbilityDisplayUI();

	Hudson::Render::SpriteComponent* _abilityFrameUISprite;
	Hudson::Render::SpriteComponent* _frameSprite;
	Hudson::World::Scene* _currentScene;
	Hudson::Render::SpriteComponent* _abilitySprite;

	Hudson::Render::SpriteComponent* _highlightSprite;
	Hudson::Entity::GameObject* HighlightObject;
	Player* _currentPlayer;
	glm::uvec2 _currentPos;

	void FromJson(const nlohmann::json& j) override;
	void ToJson(nlohmann::json& j) override;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;
	void DrawPropertyUI() override;
};

