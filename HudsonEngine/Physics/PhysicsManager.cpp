#include "PhysicsManager.h"
#include "../Entity/GameObject.h"
#include "../Common/Engine.h"
#include "../World/Scene.h"
#include "../Physics/PhysicsComponent.h"
#include "../Physics/ColliderComponent.h"

Hudson::Physics::PhysicsManager::PhysicsManager(Hudson::Common::Engine* engine) : _engine(engine)
{
	_lastTime = glfwGetTime();
	_timer = _lastTime;
	_accumulator = 0;
	_nowTime = 0;
	_frames = 0;
	_updates = 0;
}

Hudson::Physics::PhysicsManager::~PhysicsManager()
{
	delete _physics;
	_physics = nullptr;
}

void Hudson::Physics::PhysicsManager::UpdatePhysics()
{
	_nowTime = glfwGetTime();
	_accumulator += ((_nowTime - _lastTime) / FPS_60);
	_lastTime = _nowTime;

	// todo remove this debug
	//std::cout << "dt = " << _accumulator << "\n";

	// Only _updates at 60 _frames / s - Physics and any 60FPS locked stuff here
	while (_accumulator >= 1.0f)
	{
		//_physics->Update(deltaTime);
		UpdateMovement(FPS_60);
		UpdateCollider();
		_updates++;
		_accumulator--;
	}

	// Renders at maximum possible _frames - Render Here
	_frames++;

	// Reset after one second
	if (glfwGetTime() - _timer > 1.0f)
	{
		_timer++;
		std::cout << "FPS: " << _updates << std::endl;
		_updates = 0, _frames = 0;
	}
}

void Hudson::Physics::PhysicsManager::UpdateMovement(float deltaTime)
{
	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	for (auto scene : scenes)
	{
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

