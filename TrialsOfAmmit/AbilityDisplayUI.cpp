#include "AbilityDisplayUI.h"

AbilityDisplayUI::AbilityDisplayUI(glm::vec2 spawnPos, Hudson::World::Scene* _Scene, Player* _player) : Behaviour ("AbilityUI")
{
	_currentScene = _Scene;

	_currentPos = spawnPos;
	

	_currentPlayer = _player;
}

AbilityDisplayUI::~AbilityDisplayUI()
{
}

void AbilityDisplayUI::FromJson(const nlohmann::json& j)
{
}

void AbilityDisplayUI::ToJson(nlohmann::json& j)
{
}

void AbilityDisplayUI::OnCreate()
{
	//Makes the frame 
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_abilityFrameUISprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("UIFrame"));
	_abilityFrameUISprite->SetGridSize(glm::vec2(1, 1));
	_abilityFrameUISprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	_parent->AddComponent(_abilityFrameUISprite);
	_parent->SetName("AbilityUIFrame");
	_parent->GetTransform().scale = (glm::vec2(64, 64));
	_abilityFrameUISprite->SetDepthOrder(1);
	_parent->GetTransform().pos = _currentPos;


	//Makes the sprite for the ability UI icon
	Hudson::Entity::GameObject* AbilityUISprite = new Hudson::Entity::GameObject();
	_abilitySprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Abilitys"));
	_abilitySprite->SetGridSize(glm::vec2(5, 1));
	_abilitySprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_abilitySprite->SetGridPos(glm::vec2(0, 1));
	_abilitySprite->SetDepthOrder(2);
	AbilityUISprite->SetName("AbilityUIIcon");
	AbilityUISprite->GetTransform().pos = _currentPos;
	AbilityUISprite->GetTransform().scale = (glm::vec2(64, 64));
	AbilityUISprite->AddComponent(_abilitySprite);
	_currentScene->AddObject(AbilityUISprite);	


	HighlightObject = new Hudson::Entity::GameObject();
	_highlightSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Highlight"));
	_highlightSprite->SetGridSize(glm::vec2(1, 1));
	_highlightSprite->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_highlightSprite->SetGridPos(glm::vec2(0, 1));
	_highlightSprite->SetDepthOrder(10);
	HighlightObject->SetName("AbilityUIIcon");
	HighlightObject->GetTransform().pos = _currentPos;
	HighlightObject->GetTransform().scale = (glm::vec2(64, 64));
	HighlightObject->AddComponent(_highlightSprite);
	_currentScene->AddObject(HighlightObject);
}

void AbilityDisplayUI::OnTick(const double& dt)
{
	if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>() != nullptr)
	{
		if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_ROLL)
		{
			_abilitySprite->SetGridPos(glm::vec2(0, 1));
		}
		if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_STUN)
		{
			_abilitySprite->SetGridPos(glm::vec2(1, 1));
		}
		if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_RAGE)
		{
			_abilitySprite->SetGridPos(glm::vec2(2, 1));
		}
		if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_HEAL)
		{
			_abilitySprite->SetGridPos(glm::vec2(3, 1));
		}
		if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityType == AT_AOEDAMAGE)
		{
			_abilitySprite->SetGridPos(glm::vec2(4, 1));
		}
	}

	if (_currentPlayer->GetParent()->GetComponent<AbilityHolder>() != nullptr)
	{
		float percentage = _currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_timer / _currentPlayer->GetParent()->GetComponent<AbilityHolder>()->_currentAbility->_abilityCoolDownTime;

		HighlightObject->GetTransform().scale.y = 64 * percentage;
	}
	
	
}

void AbilityDisplayUI::OnDestroy()
{
}

void AbilityDisplayUI::DrawPropertyUI()
{
}
