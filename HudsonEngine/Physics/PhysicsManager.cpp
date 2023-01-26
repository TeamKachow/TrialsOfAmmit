#include "../Physics/PhysicsManager.h"
#include "../Entity/GameObject.h"
#include "../Common/Engine.h"
#include "../World/Scene.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/ColliderComponent.h"
#include "../Util/Timestep.h"

Hudson::Physics::PhysicsManager::PhysicsManager(Hudson::Common::Engine* engine) : _engine(engine)
{
	_physics = new Hudson::Physics::PhysicsComponent();

	_collider = new Hudson::Physics::ColliderComponent();

	_timestep = new Hudson::Util::Timestep([&](const double dt)
		{
			UpdateMovement(dt);
			UpdateCollider();
		});
}

Hudson::Physics::PhysicsManager::~PhysicsManager()
{
	delete _physics;
	_physics = nullptr;

	delete _collider;
	_collider = nullptr;

	delete _timestep;
	_timestep = nullptr;
}

void Hudson::Physics::PhysicsManager::UpdatePhysics()
{
	_timestep->CalculateTimestep();
}

void Hudson::Physics::PhysicsManager::UpdateMovement(double deltaTime)
{
	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	for (auto scene : scenes)
	{
		// Don't run physics on inactive scenes
		if (!scene->IsActive())
			continue;

		for (auto gameObject : scene->GetObjects())
		{
			// Update Physics
			for (auto physics : gameObject->GetComponents<PhysicsComponent>())
			{
				physics->Update(deltaTime);
			}
		}
	}
}

void Hudson::Physics::PhysicsManager::UpdateCollider()
{
	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	for (auto scene : scenes)
	{
		// Don't update collisions on inactive scenes
		if (!scene->IsActive())
			continue;

		std::vector<ColliderComponent*> vecColliders;

		for (auto gameObject : scene->GetObjects())
		{
			// Update Collisions
			for (auto collider : gameObject->GetComponents<ColliderComponent>())
			{
				vecColliders.push_back(collider);
				collider->ClearColliding();
			}
		}
		for (int i = 0; i < vecColliders.size() - 1; i++)
		{
			for (int j = i + 1; j < vecColliders.size(); j++)
			{
				if (vecColliders[i]->AABBCollision(vecColliders[j]))
				{
					vecColliders[i]->SetColliding(vecColliders[j]);
					vecColliders[j]->SetColliding(vecColliders[i]);
				}
			}
		}
	}
}

