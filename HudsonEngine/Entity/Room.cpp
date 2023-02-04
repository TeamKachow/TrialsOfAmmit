#include "Room.h"

Room::Room() : Behaviour("Room")
{

}

Room::Room(const char* roomFile) : Behaviour("Room")
{
	// Determine x,y from file
	// This is debug, file will already be wrote to

	nlohmann::json roomData;
	std::ofstream writeFile(roomFile);
	roomData["roomX"] = 20;
	roomData["roomY"] = 10;
	roomData["navGrid"] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	roomData["texGrid"] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	roomData["objGrid"] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};


	roomData["texReference"] = { { {"textureID", 0}, {"gridPosX", 1}, {"gridPosY", 1}, {"textureRoot", "textures/level1room.png"}, {"gridSizeX", 15}, {"gridSizeY", 18} }, { {"textureID", 1 }, {"gridPosX", 1}, {"gridPosY", 6}, {"textureRoot", "textures/level1room.png"}, {"gridSizeX", 15}, {"gridSizeY", 18} } };

	writeFile << std::setw(1) << roomData << std::endl;

	// Read from file JSON

	std::ifstream i(roomFile);
	nlohmann::json j;
	i >> j;

	x = j["roomX"];
	y = j["roomY"];

	//_parent->GetTransform().

	nav_grid_ = new char[x * y];
	texture_grid_ = new char[x * y];

	//auto navGrid = j["navGrid"];
	//nav_grid_ = j["navGrid"].get<int>();

	//for (const auto& val : j["navGrid"].items())
	//{
	//	nav_grid_.push_back(val.value());
	//}

	//for (nlohmann::json::iterator it = j["navGrid"].begin(); it != j["navGrid"].end(); ++it) {
	//	nav_grid_.push_back(*it);
	//}

	std::string standardArray = j["navGrid"].dump();
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), '['), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ']'), standardArray.end());
	standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ','), standardArray.end());
	char* charArray = new char[standardArray.length() + 1]; // +1 for std::string null terminator
	strcpy_s(charArray, standardArray.length() + 1, standardArray.c_str());

	for(int i = 0; i < y; ++i) // 5
	{
		for (int j = 0; j < x; ++j) // 20
		{
			nav_grid_[j * y + i] = charArray[j * y + i];
			//*(nav_grid_ + j * y + i) = *(charArray + j * y + i);

			// start mem address + (currentX * maxY) + currentY
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
			texture_grid_[j * y + i] = charArray[j * y + i];
			// start mem address + (currentX * maxY) + currentY
		}
	}
	delete[] charArray;

	// map local texture ids to std::map<int, Texture*>
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	nlohmann::json texRef = j["texReference"];
	for (const auto &object : texRef)
	{
		//std::cout << object["textureRoot"];
		// TODO determine alpha channel in storage of tex
		resManager->LoadTexture(object["textureRoot"], true, "Dummy");
		
		Hudson::Render::SpriteComponent* newSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Dummy"), glm::vec2(object["gridSizeX"], object["gridSizeY"]), glm::vec2(object["gridPosX"], object["gridPosY"]));
		texture_reference_.insert({ object["textureID"], newSprite});
		//
	}

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			// relavent texID
			//std::cout << texture_grid_[j * y + i];
			int value = char(texture_grid_[j * y + i]) - 48;
			//std::cout << value;

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
	
	//standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), '['), standardArray.end());
	//standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ']'), standardArray.end());
	//standardArray.erase(std::remove(standardArray.begin(), standardArray.end(), ','), standardArray.end());
	// copying the contents of the
	// string to char array
	//strcpy(charArray, standardArray.c_str());


	//std::cout << standardArray;
	


	//std::cout << j["navGrid"];
	//std::cout << j["texReference"]["gridPosX"];
	//j

	//std::ifstream readFile(roomFile);
	//roomData = nlohmann::json::parse(readFile);


	//std::string myText;
	//int roomY = 0;
	//bool gridValid = true, textureValid = false;

	//while (std::getline(readFile, myText))
	//{
	//	if(myText != "-t") // First stage
	//	{
	//		gridValid = false;
	//		textureValid = true;
	//		x = myText.size();
	//		++roomY;

	//		std::cout << myText << std::endl;
	//		std::cout << roomY << std::endl;
	//	}
	//	else
	//	{
	//		break;
	//	}

	//	if(gridValid)
	//	{
	//		
	//	}
	//	
	//}
	//y = roomY;

	//nav_grid_ = new char[x * y];
	//std::ifstream outputFile(roomFile);
	//std::string outputText;
	//int currentRoomY = 0;

	//while (std::getline(outputFile, outputText))
	//{
	//	for(int i = 0; i < x; ++i)
	//	{
	//		*(nav_grid_ + i * y + currentRoomY) = outputText.at(i);
	//	}
	//	++currentRoomY;
	//}



	// Debug
	// print the 2D array
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			std::cout << texture_grid_[j * y + i] << " ";
		}
		std::cout << std::endl;
	}

	//for (int i = 0; i < x; i++)
	//{
	//	for (int j = 0; j < y; j++) {
	//		std::cout << *(texture_grid_ + i * y + j) << " ";
	//	}
	//	std::cout << std::endl;
	//}

}

Room::~Room()
{
	delete nav_grid_;
	delete texture_grid_;
}

void Room::OnCreate()
{
	Behaviour::OnCreate();


}

void Room::OnTick(const double& dt)
{
	for (Hudson::Render::SpriteComponent* sprite : spriteComponents) {
		_parent->AddComponent(sprite);
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
