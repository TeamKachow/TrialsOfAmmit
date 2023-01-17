#include "PhysicsManager.h"
Hudson::Physics::PhysicsManager::PhysicsManager()
{
	physics = new PhysicsMaths();
	collider = new Hudson::Collision::Collider();
}

void Hudson::Physics::PhysicsManager::UpdatePhysics()
{
	//std::cout << "PHYSICS FPS: " << deltaTime << std::endl;
	float deltaTime = time->DeltaTime();
	if (deltaTime == 0.0f)
	{
		return;
	}

	physics->Update(deltaTime);

}

void Hudson::Physics::PhysicsManager::UpdateCollisions()
{
	// float deltaTime = UpdateTime();

	// TO DO LATER
}