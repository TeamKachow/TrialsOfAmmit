#include "ColliderComponent.h"

Hudson::Physics::ColliderComponent::ColliderComponent()
{

}

Hudson::Physics::ColliderComponent::~ColliderComponent()
{

}

bool Hudson::Physics::ColliderComponent::AABBCollision(ColliderComponent* collider)
{
	AABB box1 = this->GetAABB();
	AABB box2 = collider->GetAABB();

	bool CheckCollisionX = box1.Right >= box2.Left && box2.Right >= box1.Left;

	bool CheckCollisionY = box1.Down >= box2.Up && box2.Down >= box1.Up;

	return CheckCollisionX && CheckCollisionY;
}

AABB Hudson::Physics::ColliderComponent::GetAABB()
{
	AABB box;
	box.Left = _parent->GetTransform().posX;
	box.Right = _parent->GetTransform().posX + _parent->GetTransform().scaleX;

	box.Up = _parent->GetTransform().posY;
	box.Down = _parent->GetTransform().posY + _parent->GetTransform().scaleY;

	return box;
}
