#include "PhysicsManager.h"
#include "Entity/GameObject.h"
#include "Common/Engine.h"
#include "World/Scene.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

Hudson::Physics::PhysicsManager::PhysicsManager(Hudson::Common::Engine* engine) : m_engine(engine)
{
	lastTime = glfwGetTime();
	timer = lastTime;
	accumulator = 0;
	nowTime = 0;
	frames = 0;
	updates = 0;
}

Hudson::Physics::PhysicsManager::~PhysicsManager()
{
	delete physics;
	physics = nullptr;
}

void Hudson::Physics::PhysicsManager::UpdatePhysics()
{
	nowTime = glfwGetTime();
	accumulator += ((nowTime - lastTime) / FPS_60);
	lastTime = nowTime;

	// todo remove this debug
	std::cout << "dt = " << accumulator << "\n";

	// Only updates at 60 frames / s - Physics and any 60FPS locked stuff here
	while (accumulator >= 1.0f)
	{
		//physics->Update(deltaTime);
		UpdateMovement(FPS_60);
		UpdateCollider();
		updates++;
		accumulator--;
	}

	// Renders at maximum possible frames - Render Here
	frames++;

	// Reset after one second
	if (glfwGetTime() - timer > 1.0f)
	{
		timer++;
		std::cout << "FPS: " << frames << std::endl;
		updates = 0, frames = 0;
	}
}

void Hudson::Physics::PhysicsManager::UpdateMovement(float deltaTime)
{
	auto scenes = m_engine->GetSceneManager()->GetLoadedScenes();
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
	auto scenes = m_engine->GetSceneManager()->GetLoadedScenes();
	for (auto scene : scenes)
	{
		std::vector<ColliderComponent*> vecColliders;

		for (auto gameObject : scene->GetObjects())
		{
			// Update Collisions
			for (auto collider : gameObject->GetComponents<ColliderComponent>())
			{
				vecColliders.push_back(collider);
			}
		}
		for (int i = 0; i < vecColliders.size() - 1; i++)
		{
			for (int j = i + 1; j < vecColliders.size(); j++)
			{
				if (vecColliders[i]->AABBCollision(vecColliders[j]))
				{
					std::cout << "COLLISION DETECTED" << std::endl;
				}
			}
		}
	}
}

