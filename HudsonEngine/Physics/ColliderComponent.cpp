#include "ColliderComponent.h"

Hudson::Physics::ColliderComponent::ColliderComponent() : Component("Box Collider")
{

}

Hudson::Physics::ColliderComponent::ColliderComponent(float newXOffset, float newYOffset) : Component("Box Collider")
{
	xOffset = newXOffset;
	yOffset = newYOffset;
}

Hudson::Physics::ColliderComponent::~ColliderComponent()
{

}

void Hudson::Physics::ColliderComponent::SetColliding(ColliderComponent* other)
{
	_colliderList.emplace(other);
}

void Hudson::Physics::ColliderComponent::ClearColliding()
{
	_colliderList.clear();
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

	// 0,0
	// 6 xOffset
	box.Left = _parent->GetTransform().pos.x + (_parent->GetTransform().scale.x * 0.02f); // 2%
	box.Left += _parent->GetTransform().scale.x * xOffset; // + 64*6
	// xLeft = 384

	box.Right = _parent->GetTransform().pos.x + _parent->GetTransform().scale.x - (_parent->GetTransform().scale.x * 0.02f);
	box.Right += _parent->GetTransform().scale.x * xOffset; // 64*6 // 384
	// 384+64 = 448

	box.Up = _parent->GetTransform().pos.y + (_parent->GetTransform().scale.y * 0.02f); //0
	box.Up += _parent->GetTransform().scale.y * yOffset;

	box.Down = _parent->GetTransform().pos.y + _parent->GetTransform().scale.y - (_parent->GetTransform().scale.y * 0.02f);
	box.Down += _parent->GetTransform().scale.y * yOffset;

	return box;
}

void Hudson::Physics::ColliderComponent::DrawPropertyUI()
{
	ImGui::Text("Colliding with %d objects", _colliderList.size());
    for (auto collider : _colliderList)
    {
		ImGui::BulletText("Col %p\nObj %p", collider, collider->_parent);
    }
}

void Hudson::Physics::ColliderComponent::FromJson(const nlohmann::json& j)
{
}

void Hudson::Physics::ColliderComponent::ToJson(nlohmann::json& j)
{
}
