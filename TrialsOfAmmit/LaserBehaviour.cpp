#include "LaserBehaviour.h"

LaserBehaviour::LaserBehaviour(glm::vec2 spawnPos, int laserType) : Behaviour("LaserBehavior")
{
	_laserType = laserType;

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
	if (_laserType == 0)
	{

	}
	LaserSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("LaserVert"));

}
