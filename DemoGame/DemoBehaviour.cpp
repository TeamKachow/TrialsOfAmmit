#include <Hudson.h>
#include "DemoBehaviour.h"

DemoBehaviour::DemoBehaviour(Hudson::Render::SpriteComponent* sprite, double animSpeed) : Behaviour("Demo Behaviour")
{
	_sprite = sprite;
    _animSpeed = animSpeed;
}

DemoBehaviour::~DemoBehaviour()
= default;

DemoBehaviour::DemoBehaviour() : Behaviour("Demo Behaviour"), _sprite(nullptr), _animSpeed(0.8)
{
}

void DemoBehaviour::OnCreate()
{
	// If no sprite set yet, look for one on the parent
	if (_sprite == nullptr)
	{
		const auto sprites = _parent->GetComponents<Hudson::Render::SpriteComponent>();
		if (!sprites.empty())
			_sprite = sprites[0];
	}

    std::cout << "Demo behaviour added to an object!\n";
}

void DemoBehaviour::OnTick(const double& dt)
{
	// TODO: remove this when OnCreate is implemented
	if (_sprite == nullptr)
	{
		const auto sprites = _parent->GetComponents<Hudson::Render::SpriteComponent>();
		if (!sprites.empty())
			_sprite = sprites[0];
	}

	// EXAMPLE: sprite animation
    _animAcc += dt;
    if (_animAcc >= _animSpeed)
    {
        _animAcc -= _animSpeed;

		int x = _sprite->GetGridPos().x;
		glm::vec2 spriteGridSize = _sprite->GetGridSize();

		if (x >= spriteGridSize.x - 1) {
			x = 0;
		}
		else {
			x += 1;
		}
		
		_sprite->SetGridPos(glm::vec2(x, 0));
    }


	// EXAMPLE: physics collision checks

	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			// first collider is hitting another object - handle this collision
			std::cout << this << " detected " << collider << " colllided with " << other << "\n";
		}
	}

	// EXAMPLE: screen wrapping

	auto& transform = _parent->GetTransform();
	if (transform.pos.x < 0)
		transform.pos.x = 1599;

	if (transform.pos.x > 1600)
		transform.pos.x = 1;
}

void DemoBehaviour::OnDestroy()
{
    std::cout << "Demo behaviour removed from an object!\n";
}

void DemoBehaviour::DrawPropertyUI()
{
	ImGui::DragScalar("Anim spd", ImGuiDataType_Double, &_animSpeed, 0.05);
	ImGui::Text("Acc: %lf", _animAcc);
}
