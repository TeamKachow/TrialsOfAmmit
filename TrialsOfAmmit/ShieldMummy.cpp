#include "ShieldMummy.h"

ShieldMummy::ShieldMummy(glm::vec2 spawnPos) : Behaviour("ShieldMummyBehaviour")
{
	_spawnPos = spawnPos;
}

ShieldMummy::~ShieldMummy()
{
}

void ShieldMummy::Kill()
{
	_aiDeathSprite->SetGridSize(glm::vec2(3, 1));
	_aiDeathSprite->SetGridPos(glm::vec2(1, 1));
	_aiDeathSprite->SetDepthOrder(9);
	_parent->RemoveComponent(_aiSprite);
	Blood->AddComponent(_aiDeathSprite);
	_currentScene->AddObject(Blood);
	Blood->GetTransform().pos = _parent->GetTransform().pos;
	_currentScene->RemoveObject(Blood);
	_currentScene->RemoveObject(_parent);
}

void ShieldMummy::FromJson(const nlohmann::json& j)
{
}

void ShieldMummy::ToJson(nlohmann::json& j)
{
}

void ShieldMummy::OnCreate()
{
	//sets up sprite
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_aiSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
	_aiSprite->SetGridSize(glm::vec2(3, 4));
	_aiSprite->SetDepthOrder(8);
	_aiSprite->SetColor(glm::vec3(1, 0, 0));
	_parent->AddComponent(_aiSprite);
	_parent->SetName("ShieldMummy");

	//sets up collider
	_aiCollider = new Hudson::Physics::ColliderComponent();
	_parent->AddComponent(_aiCollider);

	_aiDeathSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Blood"));
	Blood = new Hudson::Entity::GameObject;
	
	_currentScene = _parent->GetScene();
}

void ShieldMummy::OnDestroy()
{
}

void ShieldMummy::OnTick(const double& dt)
{
}
