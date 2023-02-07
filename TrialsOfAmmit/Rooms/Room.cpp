 #include "Room.h"

// Want to spawn something new include here
#include "../AiAgent.h"

Room::Room() : Behaviour("Room")
{

}

Room::Room(const char* roomFile) : Behaviour("Room")
{
	// Determine x,y from file
	// This is debug, file will already be wrote to

	nlohmann::json roomData;
	std::ofstream writeFile(roomFile);
	roomData["roomX"] = 10;
	roomData["roomY"] = 12;
	roomData["navGrid"] = {
		0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0
	};
	roomData["texGrid"] = {
		0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0
	};
	roomData["objGrid"] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,2,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0
	};


	roomData["texReference"] = { { {"textureID", 0}, {"gridPosX", 1}, {"gridPosY", 1}, {"textureRoot", "textures/level1room.png"}, {"gridSizeX", 15}, {"gridSizeY", 18} }, { {"textureID", 1 }, {"gridPosX", 1}, {"gridPosY", 6}, {"textureRoot", "textures/level1room.png"}, {"gridSizeX", 15}, {"gridSizeY", 18} } };
	writeFile << std::setw(1) << roomData << std::endl;

	// Read from file JSON

	std::ifstream i(roomFile);
	nlohmann::json j;
	i >> j;

	x = j["roomX"];
	y = j["roomY"];

	nav_grid_ = new char[x * y];
	texture_grid_ = new char[x * y];
	object_grid = new char[x * y];

	std::string standardArray = j["navGrid"].dump();
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), '['), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ']'), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ','), standardArray.end());
	char* charArray = new char[standardArray.length() + 1]; // +1 for std::string null terminator
	strcpy_s(charArray, standardArray.length() + 1, standardArray.c_str());

	for(int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			nav_grid_[i * x + j] = charArray[i * x + j];
		}
	}
	delete[] charArray;

	standardArray = j["texGrid"].dump();
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), '['), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ']'), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ','), standardArray.end());
	charArray = new char[standardArray.length() + 1]; // +1 for std::string null terminator
	strcpy_s(charArray, standardArray.length() + 1, standardArray.c_str());

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			texture_grid_[i * x + j] = charArray[i * x + j];
		}
	}
	delete[] charArray;

	standardArray = j["objGrid"].dump();
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), '['), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ']'), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ','), standardArray.end());
	charArray = new char[standardArray.length() + 1]; // +1 for std::string null terminator
	strcpy_s(charArray, standardArray.length() + 1, standardArray.c_str());

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			object_grid[i * x + j] = charArray[i * x + j];
		}
	}
	delete[] charArray;

	// map local texture ids to std::map<int, Texture*>
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	nlohmann::json texRef = j["texReference"];
	for (const auto &object : texRef)
	{
		// TODO determine alpha channel in storage of tex
		resManager->LoadTexture(object["textureRoot"], true, "Dummy");
		
		Hudson::Render::SpriteComponent* newSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Dummy"), glm::vec2(object["gridSizeX"], object["gridSizeY"]), glm::vec2(object["gridPosX"], object["gridPosY"]));
		texture_reference_.insert({ object["textureID"], newSprite});
	}

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			// relevant texID
			int value = char(nav_grid_[i * x + j]) - 48; // This isn't a great solution but due to time constraints im sticking with this flaw in the planned design
			if(value == 0)
			{
				Hudson::Physics::ColliderComponent* newCollider = new Hudson::Physics::ColliderComponent(j, i);
				
				colliderComponents.push_back(newCollider);
			}

		}
	}


	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			// relevant texID
			int value = char(texture_grid_[i * x + j]) - 48;

			if (texture_reference_.find(value) != texture_reference_.end()) {
				// Do something related to texture
				// Add component blah blah
				Hudson::Render::SpriteComponent* newSprite = new Hudson::Render::SpriteComponent(*texture_reference_.find(value)->second);
				newSprite->SetXOffset(j);
				newSprite->SetYOffset(i);
				newSprite->SetDepthOrder(0);
				spriteComponents.push_back(newSprite);
			}

		}
	}

	// Debug
	// print the 2D array
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			std::cout << texture_grid_[i * x + j] << " ";
		}
		std::cout << std::endl;
	}

}

Room::~Room()
{
	delete nav_grid_;
	delete texture_grid_;
}

void Room::OnCreate()
{
	Behaviour::OnCreate();

	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	// 1 = Player
	// 2 = Mummy AI

	// I want to spawn game object, how do I determine what to spawn based on some things

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			// relevant texID
			int value = char(object_grid[i * x + j]) - 48;
			if (value == 1) {

			}
			else if (value == 2) {
				// Spawn Mummy AI
				Hudson::Render::SpriteComponent* spriteComponent = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Mummy"));
				spriteComponent->SetGridSize(glm::vec2(3, 4));
				spriteComponent->SetDepthOrder(1);

				Hudson::Physics::PhysicsComponent* physicComponent = new Hudson::Physics::PhysicsComponent();
				physicComponent->SetMass(1.0f);
				physicComponent->SetAcceleration(glm::vec2(10, 0), true);

				Hudson::Physics::ColliderComponent* colliderComponent = new Hudson::Physics::ColliderComponent();

				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Mummy");
				newObject->AddComponent(physicComponent);
				newObject->AddComponent(colliderComponent);
				newObject->AddComponent(spriteComponent);
				newObject->AddComponent(new AiAgent(spriteComponent, 0));

				newObject->GetTransform().pos.x = j * newObject->GetTransform().scale.x;
				newObject->GetTransform().pos.y = i * newObject->GetTransform().scale.y;

				// Get room parent - get scene - add new game object to scene
				_parent->GetScene()->AddObject(newObject);
			}

		}
	}

}

void Room::OnTick(const double& dt)
{
	for (Hudson::Render::SpriteComponent* sprite : spriteComponents) {
		_parent->AddComponent(sprite);
	}
	for (Hudson::Physics::ColliderComponent* collider : colliderComponents) {
		_parent->AddComponent(collider);
	}





}

void Room::OnDestroy()
{
	Behaviour::OnDestroy();
	//std::map<int, Hudson::Render::SpriteComponent*>::iterator iter;
	//for (iter = texture_reference_.begin(); iter != texture_reference_.end(); ++iter)
	//{
	//	_parent->RemoveComponent(iter->second);
	//}
}

void Room::DrawPropertyUI()
{

}
