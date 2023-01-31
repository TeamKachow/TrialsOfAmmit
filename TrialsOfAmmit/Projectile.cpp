#include "Projectile.h"


Projectile::Projectile(facingDirections projectileDirection, glm::vec2 spawnPos, Hudson::World::Scene* CurrentScene, Hudson::Entity::GameObject* _projectileRef) : Behaviour("ProjectileBehaviour")
{
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();
	_projectileSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Projectile"));
	_projectilePhysics = new Hudson::Physics::PhysicsComponent();
	Hudson::Physics::ColliderComponent* _projectileCollider = new Hudson::Physics::ColliderComponent();

	_projectileSprite->SetGridSize(glm::vec2(3, 4));
	_projectileSprite->SetGridPos(glm::vec2(0, 0));
	_projectilePhysics->SetMass(1.0f);

	_projectile = _projectileRef;
	_projectile->AddComponent(_projectileSprite);
	_projectile->AddComponent(_projectilePhysics);
	_projectile->AddComponent(_projectileCollider);

	_projectileDirection = projectileDirection;

	_projectile->GetTransform().pos = spawnPos;
	_currentScene = CurrentScene;
	_currentScene->AddObject(_projectile);
}

Projectile::~Projectile()
{

}

void Projectile::OnCreate()
{
	switch (_projectileDirection)
	{
	case Down:
		_projectilePhysics->SetVelocity(glm::vec2(0, 250));
		_projectileSprite->SetGridPos(glm::vec2(0, 3));
		break;
	case Left:
		_projectilePhysics->SetVelocity(glm::vec2(-250, 0));
		_projectileSprite->SetGridPos(glm::vec2(0, 2));
		break;
	case Right:
		_projectilePhysics->SetVelocity(glm::vec2(250, 0));
		_projectileSprite->SetGridPos(glm::vec2(0, 1));
		break;
	case Up:
		_projectilePhysics->SetVelocity(glm::vec2(0, -250));
		_projectileSprite->SetGridPos(glm::vec2(0, 0));
		break;
	case Stopped: 
		break;
	default: ;
	}
}

void Projectile::OnTick(const double& dt)
{

}

void Projectile::OnDestroy()
{
	Behaviour::OnDestroy();
}

void Projectile::DrawPropertyUI()
{
}
