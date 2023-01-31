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
	_projectile->SetName("Projectile");

	_projectileDirection = projectileDirection;

	_animTimer = 0;
	_animSpeed = 0.2;

	_deleteTime = 1;
	_deleteTimer = 0;

	_spawnPos = spawnPos;

	
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
		_projectile->GetTransform().pos.y = _spawnPos.y + 50 ;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 3;
		break;
	case Left:
		_projectilePhysics->SetVelocity(glm::vec2(-250, 0));
		_projectile->GetTransform().pos.x = _spawnPos.x - 50;
		_projectile->GetTransform().pos.y = _spawnPos.y;
		_gridY = 2;
		break;
	case Right:
		_projectilePhysics->SetVelocity(glm::vec2(250, 0));
		_projectile->GetTransform().pos.x = _spawnPos.x + 50;
		_projectile->GetTransform().pos.y = _spawnPos.y;
		_gridY = 1;
		break;
	case Up:
		_projectilePhysics->SetVelocity(glm::vec2(0, -250));
		_projectile->GetTransform().pos.y = _spawnPos.y - 50;
		_projectile->GetTransform().pos.x = _spawnPos.x;
		_gridY = 0;
		break;
	case Stopped: 
		break;
	default: ;
	}
	_projectileSprite->SetGridPos(glm::vec2(_gridX, _gridY));
}

void Projectile::OnTick(const double& dt)
{
	_animTimer += dt;
	_deleteTimer += dt;
	if(_animTimer >= _animSpeed )
	{
		_animTimer -= _animSpeed;
		_gridX++;
		_projectileSprite->SetGridPos(glm::vec2(_gridX, _gridY));
	}
	if(_deleteTimer >= _deleteTime)
	{
		_currentScene->RemoveObject(_projectile);
	}



}

void Projectile::OnDestroy()
{
	Behaviour::OnDestroy();
}

void Projectile::DrawPropertyUI()
{
}