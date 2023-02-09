#include "Door.h"

Door::Door() : Behaviour("DoorBehaviour")
{

}

Door::~Door()
{

}

void Door::OnCreate()
{
	Room* tempRoom = CurrentRoom->GetComponent<Room>();
	_player->SetPosition(vec2(tempRoom->GetRoomSize().x * tempRoom->GetParent()->GetTransform().scale.x / 2, tempRoom->GetRoomSize().y * tempRoom->GetParent()->GetTransform().scale.y));
	DoorCollider = new Hudson::Physics::ColliderComponent;
	_parent->AddComponent(DoorCollider);
	_isActive = false;
	_activeSpeed = 1;
	

	_minRange = 0;
	_maxRange = 1;

	auto _sceneObjects = _parent->GetScene()->GetObjects();
	for (Hudson::Entity::GameObject* other : _sceneObjects)
	{
		if (other->GetName() == "Player")
		{
			_player = other->GetComponent<Player>();
			break;
		}
	}
}

void Door::OnDestroy()
{

}

void Door::OnTick(const double& dt)
{
	CollisionCheck();
	_ativeTimer += dt;
	if (_ativeTimer > _activeSpeed)
	{
		_isActive = true;
	}
}

void Door::DrawPropertyUI()
{

}

void Door::FromJson(const nlohmann::json& j)
{

}

void Door::ToJson(nlohmann::json& j)
{

}

void Door::CollisionCheck()
{
	std::vector<Hudson::Physics::ColliderComponent*> colliders = _parent->GetComponents<Hudson::Physics::ColliderComponent>();
	if (!colliders.empty())
	{
		Hudson::Physics::ColliderComponent* collider = colliders.at(0);
		auto collidingWith = collider->GetCurrentCollisions();
		for (auto other : collidingWith)
		{
			if (other->GetParent()->GetComponent<Player>() != nullptr)
			{
				Player* _playerCollision = other->GetParent()->GetComponent<Player>();
				if (_playerCollision != nullptr)
				{
					GenerateNewRoom();
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void Door::GenerateNewRoom()
{
	
	random_device rand;
	uniform_int_distribution<int> dist(_minRange, _maxRange);
	RandRoomNum = dist(rand);

	Roomname = "Rooms/room" + to_string(RandRoomNum) + ".room";
	CurrentRoom = new Hudson::Entity::GameObject;
	CurrentRoom->AddComponent(new class Room (Roomname.c_str()));
	MovePlayer();
}

void Door::MovePlayer()
{	
	Room* oldRoom = CurrentRoom->GetComponent<Room>();
	_parent->RemoveComponent(oldRoom);
}
