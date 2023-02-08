#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include "Behaviour.h"
#include "GameObject.h"
#include "../Common/ResourceManager.h"
#include "../Common/IEditable.h"
#include "../Render/SpriteComponent.h"
#include "../Physics/ColliderComponent.h"
#include "../Util/stdafx.h"

class Room : public Hudson::Entity::Behaviour, public Hudson::Common::IEditable
{
public:
	Room();
	Room(const char* roomFile);
	~Room() override;

	void OnCreate() override;
	void OnTick(const double& dt) override;
	void OnDestroy() override;

	void DrawPropertyUI() override;

private:
	int x, y;
	
	char* nav_grid_; // dynamic array 
	char* texture_grid_; // dynamic array 
	char* object_grid; // dynamic array

	std::map<int, Hudson::Render::SpriteComponent*> texture_reference_;
	std::map<int, Hudson::Entity::GameObject*> obj_reference_;

	std::vector<Hudson::Render::SpriteComponent*> spriteComponents;
	std::vector<Hudson::Physics::ColliderComponent*> colliderComponents;
};

struct textureRefData {
	int textureID = 0;
	int gridPosX = 0;
	int gridPosY = 0;
	int gridSizeX = 1;
	int gridSizeY = 1;
	std::string textureRoot = "";

	void Clear() {
		textureID = 0;
		gridPosX = 0;
		gridPosY = 0;
		gridSizeX = 1;
		gridSizeY = 1;
		textureRoot = "";
	}
};

struct tileData{
	bool isSolid = false;
	int textureRef = 0;
	int objectRef = 0;
};

struct ImGuiRoomData
{
	int roomX = 10;
	int roomY = 10;
	bool isResizing = false;

	tileData* selected = nullptr;
	tileData* roomGrid = new tileData[roomX * roomY];

	std::vector<textureRefData*> textureRefs;

	void saveToFile(const char* filePath)
	{
		nlohmann::json roomData;
		std::ofstream writeFile(filePath);
		roomData["roomX"] = roomX;
		roomData["roomY"] = roomY;

		//roomData["navGrid"] =
		char* navGridChar = new char[roomX * roomY];
		char* texGridChar = new char[roomX * roomY];
		char* objGridChar = new char[roomX * roomY];

		std::string refTextureFinalString;

		for(int y = 0; y < roomY; ++y)
		{
			for (int x = 0; x < roomX; ++x)
			{
				tileData tile = roomGrid[y * roomX + x];

				if(tile.isSolid)
				{
					navGridChar[y * roomX + x] = '1';
				}
				else
				{
					navGridChar[y * roomX + x] = '0';
				}

				//texGridChar[y * roomX + x] = char(tile.textureRef);
				//objGridChar[y * roomX + x] = char(tile.objectRef;
			}
		}

		for (textureRefData* refData : textureRefs)
		{
			std::string refObject;

			refObject.append("{ ");
			refObject.append(R"("textureID":)");
			refObject.append(std::to_string(refData->textureID));

			refObject.append(R"("textureRoot":)");
			refObject.append(R"(")" + refData->textureRoot + R"(",)");

			refObject.append(R"("gridSizeX":)");
			refObject.append(std::to_string(refData->gridSizeX));

			refObject.append(R"("gridSizeY":)");
			refObject.append(std::to_string(refData->gridSizeY));

			refObject.append(R"("gridPosX":)");
			refObject.append(std::to_string(refData->gridPosX));

			refObject.append(R"("gridPosY":)");
			refObject.append(std::to_string(refData->gridPosY));

			refObject.append(" }");

			//refObject.append("\"textureRoot\":");
			//refObject.append("\""+refData->textureRoot+"\",\n");

			//refObject.append("\"gridSizeX\":");
			//refObject.append("\"" + std::to_string(refData->gridSizeX) + "\",\n");

			//refObject.append("\"gridSizeY\":");
			//refObject.append("\"" + std::to_string(refData->gridSizeY) + "\",\n");

			//refObject.append("\"gridPosX\":");
			//refObject.append("\"" + std::to_string(refData->gridPosX) + "\",\n");

			//refObject.append("\"gridPosY\":");
			//refObject.append("\"" + std::to_string(refData->gridPosY) + "\",\n");

			refTextureFinalString.append(refObject);
		}

		roomData["navGrid"] = navGridChar;
		//roomData["texGrid"] = texGridChar;
		//roomData["objGrid"] = objGridChar;
		roomData["texReference"] = { refTextureFinalString };

		writeFile << std::setw(1) << roomData << std::endl;

	}

	void updateRoomSize(int currentRoomX, int currentRoomY) {
		
		if (isResizing == false) {
			isResizing = true;

			// make temp copy
			int size = (currentRoomX * currentRoomY) * 2;
			tileData* tempGridData = new tileData[size];
			for (int i = 0; i < size; ++i) {
				tempGridData[i] = roomGrid[i];
			}
			roomGrid = tempGridData;

			isResizing = false;
		}
	}
};

void StartRoomMaker(bool& isActive);