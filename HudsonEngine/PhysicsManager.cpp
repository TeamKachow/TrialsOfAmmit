#include "PhysicsManager.h"
#include <iostream>
Hudson::Physics::PhysicsManager::PhysicsManager()
{
	physics = new Hudson::Physics::PhysicsMaths();
	collider = new Hudson::Collision::Collider();

	lastTime = glfwGetTime();
	timer = lastTime;
	deltaTime = 0;
	nowTime = 0;
	frames = 0;
	updates = 0;
}

Hudson::Physics::PhysicsManager::~PhysicsManager()
{
	delete physics;
	physics = nullptr;
	delete collider;
	collider = nullptr;
}

void Hudson::Physics::PhysicsManager::UpdatePhysics()
{
	nowTime = glfwGetTime();
	deltaTime += ((nowTime - lastTime) / FPS_60);
	lastTime = nowTime;

	// Only updates at 60 frames / s - Physics and any 60FPS locked stuff here
	while (deltaTime >= 1.0f)
	{
		physics->Update(deltaTime);
		updates++;
		deltaTime--;
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