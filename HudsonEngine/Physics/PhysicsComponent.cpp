#include "../Physics/PhysicsComponent.h"
#include "../Entity/GameObject.h"

Hudson::Physics::PhysicsComponent::PhysicsComponent() : Component("Physics")
{

}

Hudson::Physics::PhysicsComponent::~PhysicsComponent()
{

}


void Hudson::Physics::PhysicsComponent::Update(double deltaTime)
{
	// Using Semi-Implicit Euler Integration

	// Calculate Acceleration Or Constant Acceleration
	CalculateAcceleration(deltaTime); 
	//CalculateConstantAcceleration(deltaTime);

	// Calculate Velocity using Acceleration
	CalculateVelocity(deltaTime);

	// Update Positions
	UpdatePosition(deltaTime);
}

void Hudson::Physics::PhysicsComponent::CalculateAcceleration(float deltaTime)
{
	// a = f / m

	if(_constantAccel == true)
	{
		_acceleration = _acceleration * deltaTime + 0.5f * _acceleration * deltaTime * deltaTime;
	}
	else
	{
		_acceleration = _force / _mass;
	}
}

void Hudson::Physics::PhysicsComponent::DrawPropertyUI()
{
	ImGui::DragFloat("Mass", &_mass, 0.1, 0.0001);
	ImGui::DragFloat2("Velocity", &_velocity.x, 0.5);
	ImGui::DragFloat2("Acceleration", &_acceleration.x, 0.5);
	ImGui::DragFloat2("Force", &_force.x, 0.5);
	ImGui::Checkbox("Const Accel.", &_constantAccel);
}

void Hudson::Physics::PhysicsComponent::CalculateVelocity(float deltaTime)
{
	// v = u + at 
	_velocity = _velocity + _acceleration * deltaTime;
}

void Hudson::Physics::PhysicsComponent::UpdatePosition(float deltaTime)
{
	Hudson::Entity::GameObject::Transform tempTrans = _parent->GetTransform();

	tempTrans.pos.x += _velocity.x * deltaTime;
	tempTrans.pos.y += _velocity.y * deltaTime;

	_parent->SetTransform(tempTrans);
}