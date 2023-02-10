#include <Hudson.h>
#include "DemoBehaviour.h"

DemoBehaviour::DemoBehaviour(Hudson::Render::SpriteComponent* sprite, double animSpeed) : Behaviour("Demo Behaviour")
{
	_sprite = sprite;
    _animSpeed = animSpeed;
}

DemoBehaviour::~DemoBehaviour()
= default;

void DemoBehaviour::OnCreate()
{
	// If no sprite set yet, look for one on the parent
	if (_sprite == nullptr)
	{
		const auto sprites = _parent->GetComponents<Hudson::Render::SpriteComponent>();
		if (!sprites.empty())
			_sprite = sprites[0];
	}

	Hudson::Audio::AudioManager* audio = GetAudioManager();
	audio->loadSoundFile("../audio/EnemyGrowl.wav");

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
	//if (!colliders.empty())
	//{
	//	Hudson::Physics::ColliderComponent* collider = colliders.at(0);
	//	auto collidingWith = collider->GetCurrentCollisions();
	//	for (auto other : collidingWith)
	//	{
	//		// first collider is hitting another object - handle this collision
	//		std::cout << this << " detected " << collider << " colllided with " << other << "\n";
	//	}
	//}

	// EXAMPLE: screen wrapping

	auto& transform = _parent->GetTransform();
	if (transform.pos.x < 0)
	{
		_parent->GetScene()->RemoveObject(_parent);
	}

	if (transform.pos.x > 1600)
		transform.pos.x = 1;

	// TODO to help devs
	// EXAMPLE: Audio loads/plays when two objects collide, unloads/stops sounds when no longer in use

	Hudson::Audio::AudioManager* audio = GetAudioManager();
	bool soundPlayed = false;
	
	// Check for collision
	//if (!colliders.empty())
	//{
	//	Hudson::Physics::ColliderComponent* collider = colliders.at(0);
	//	auto collidingWith = collider->GetCurrentCollisions();
	//	for (auto other : collidingWith)
	//	{
	//		if (!soundPlayed)
	//		{

	//			// Load and play sound
	//			audio->setSoundVolume("../audio/EnemyGrowl.wav", 0.0f);
	//			audio->playSound("../audio/EnemyGrowl.wav", false, 0.0f, 0.0f);
	//			
	//			
	//			std::cout << "Audio file has been played." << std::endl;
	//			soundPlayed = true;

	//		}
	//		else
	//		{
	//			std::cout << "Audio file could not be played." << std::endl;
	//		}
	//	}
	//}
	//else
	//{
	//	// No collisions, stop and unload sound
	//	audio->stopSound("../audio/EnemyGrowl.wav", false, 0.0f, 0.0f);
	//	soundPlayed = false;

	//};
	
}

void DemoBehaviour::OnDestroy()
{
	Hudson::Audio::AudioManager* audio = GetAudioManager();
    std::cout << "Demo behaviour removed from an object!\n";
	audio->unloadSoundFile("../audio/EnemyGrowl.wav");
	
}

void DemoBehaviour::DrawPropertyUI()
{
	ImGui::DragScalar("Anim spd", ImGuiDataType_Double, &_animSpeed, 0.05);
	ImGui::Text("Acc: %lf", _animAcc);
}

void DemoBehaviour::FromJson(const nlohmann::json& j)
{
	_animSpeed = j.at("animSpeed");
}

void DemoBehaviour::ToJson(nlohmann::json& j)
{
	j["animSpeed"] = _animSpeed;
}
