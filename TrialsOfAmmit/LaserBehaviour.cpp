#include "LaserBehaviour.h"

LaserBehaviour::LaserBehaviour(glm::vec2 spawnPos) : Behaviour("LaserBehavior")
{

}

LaserBehaviour::~LaserBehaviour()
{
}

void LaserBehaviour::Charge()
{
}

void LaserBehaviour::DeActivate()
{
}

void LaserBehaviour::OnCreate()
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	LaserSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("LaserVert"));

}
