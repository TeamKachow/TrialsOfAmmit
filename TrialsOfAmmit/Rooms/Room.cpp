#include "Room.h"

// Want to spawn something new include here
#include "../Player.h"
#include "../AiAgent.h"
#include "../Chest.h"
#include "../Door.h"
#include "../AnubisBoss.h"


Room::Room() : Behaviour("Room")
{

}

Room::Room(const char* roomFile) : Behaviour("Room")
{
	// Read from file JSON
	roomName = roomFile;
	std::ifstream i(roomFile);
	nlohmann::json json;
	i >> json;

	x = json["roomX"];
	y = json["roomY"];

	int expectedSize = x * y;
	nav_grid_ = json.at("navGrid").get<std::vector<int8_t>>();
	texture_grid_ = json.at("texGrid").get<std::vector<int8_t>>();
	object_grid = json.at("objGrid").get<std::vector<int8_t>>();

	if (nav_grid_.size() != expectedSize || texture_grid_.size() != expectedSize || object_grid.size() != expectedSize)
	{
		Hudson::Util::Debug::LogError(std::format("Wrong grid size! Expected {}, got nav = {}, tex = {}, obj = {}", expectedSize, nav_grid_.size(), texture_grid_.size(), object_grid.size()));
	}
	
	// map local texture ids to std::map<int, Texture*>
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	nlohmann::json texRef = json["texReference"];
	for (const auto &object : texRef)
	{
		// TODO determine alpha channel in storage of tex
		resManager->LoadTexture(object["textureRoot"], true, "Dummy");
		
		Hudson::Render::SpriteComponent* newSprite = new Hudson::Render::SpriteComponent(resManager->GetShader("spriteShader"), resManager->GetTexture("Dummy"), glm::vec2(object["gridSizeX"], object["gridSizeY"]), glm::vec2(object["gridPosX"], object["gridPosY"]));
		newSprite->SetDepthOrder(0);
		texture_reference_.insert({ object["textureID"], newSprite});

	}

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			// relevant texID
			int value = nav_grid_[i * x + j]; // This isn't a great solution but due to time constraints im sticking with this flaw in the planned design
			if(value == 1)
			{
				std::cout << "collider at " << j << "," << i << " idx " << i * x + j << "\n";
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
			int value = texture_grid_[i * x + j];

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
			std::cout << (int)nav_grid_[i * x + j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			std::cout << (int)texture_grid_[i * x + j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			std::cout << (int)object_grid[i * x + j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

Room::~Room()
{
}

void Room::OnCreate()
{
	Behaviour::OnCreate();

	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	// 1 = Player
	// 2 = Mummy AI
	// 3 = Chest
	// 4 = MiscObject

	// Based on roomX and roomY

	int maxRoomX = 25;
	int maxRoomY = 14;

	int offsetAmountX = (maxRoomX - x) * _parent->GetTransform().scale.x / 2;
	int offsetAmountY = (maxRoomY - y) * _parent->GetTransform().scale.y / 2;

	_parent->GetTransform().pos.x = offsetAmountX;
	_parent->GetTransform().pos.y = offsetAmountY;



	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			// relevant texID
			int value = object_grid[i * x + j];
			if (value == 1) {
				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Player");
				newObject->AddComponent(new Player(_parent->GetTransform().pos + glm::vec2(j * _parent->GetTransform().scale.x, i * _parent->GetTransform().scale.y)));

				// Get room parent - get scene - add new game object to scene
				_parent->GetScene()->AddObject(newObject);
			}
			else if (value == 2) {
				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Mummy");
				newObject->AddComponent(new AiAgent(_parent->GetTransform().pos + glm::vec2(j * newObject->GetTransform().scale.x, i * newObject->GetTransform().scale.y)));

				// Get room parent - get scene - add new game object to scene
				_parent->GetScene()->AddObject(newObject);
			}
			else if (value == 3) {
				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Chest");
				newObject->AddComponent(new Chest((_parent->GetTransform().pos + glm::vec2(j * newObject->GetTransform().scale.x, i * newObject->GetTransform().scale.y))));

				// Get room parent - get scene - add new game object to scene
				_parent->GetScene()->AddObject(newObject);
			}
			else if (value == 4) {
				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Door");
				newObject->AddComponent(new Door());
				newObject->GetTransform().pos = (_parent->GetTransform().pos + glm::vec2(j * newObject->GetTransform().scale.x, i * newObject->GetTransform().scale.y));
				// Get room parent - get scene - add new game object to scene
				_parent->GetScene()->AddObject(newObject);
			}
			else if (value == 5) {
				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Anubis");
				newObject->AddComponent(new AnubisBoss());
				newObject->GetTransform().pos = (_parent->GetTransform().pos + glm::vec2(j * newObject->GetTransform().scale.x, i * newObject->GetTransform().scale.y));
				// Get room parent - get scene - add new game object to scene
				_parent->GetScene()->AddObject(newObject);
			}
			else if (value == 6) {
				Hudson::Entity::GameObject* newObject = new Hudson::Entity::GameObject();
				newObject->SetName("Laser");
				newObject->AddComponent(new LaserBehaviour());
				newObject->GetTransform().pos = (_parent->GetTransform().pos + glm::vec2(j * newObject->GetTransform().scale.x, i * newObject->GetTransform().scale.y));
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
}

void Room::DrawPropertyUI()
{
	ImGui::Text("Room: ", roomName.c_str());
	ImGui::Text("Dimensions: %d, %d", x, y);
}

void Room::FromJson(const nlohmann::json& j)
{
}

void Room::ToJson(nlohmann::json& j)
{
}


ImGuiRoomData imguiRoomData;
bool addingTextureRef = false;
textureRefData newRefData;
char openFileName[128] = "";
char saveFileName[128] = "";

void ObjectList() {
	Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

	ImGuiIO& io = ImGui::GetIO();
	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImVec2 imageSize = ImVec2(128, 128);
	ImVec2 uv_min = ImVec2(1.0f, 0.0f); // Top-left
	ImVec2 uv_max = ImVec2(0.0f, 1.0f); // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
	
	ImTextureID playerID = reinterpret_cast<ImTextureID>(resManager->GetTexture("Player")->ID);
	ImTextureID mummyID = reinterpret_cast<ImTextureID>(resManager->GetTexture("Mummy")->ID);
	ImTextureID chestID = reinterpret_cast<ImTextureID>(resManager->GetTexture("Chest")->ID);
	ImTextureID anubisID = reinterpret_cast<ImTextureID>(resManager->GetTexture("Anubis")->ID);
	ImTextureID laserID = reinterpret_cast<ImTextureID>(resManager->GetTexture("LaserVert")->ID);

	ImGui::Text("ID: 1 - Player");
	ImGui::Image(playerID, ImVec2(96, 128), uv_min, uv_max, tint_col, border_col);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float region_sz = 64.0f;
		float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
		float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
		float zoom = 4.0f;

		imageSize = ImVec2(48, 64);

		if (region_x < 0.0f) { region_x = 0.0f; }
		else if (region_x > imageSize.x - region_sz) { region_x = imageSize.x - region_sz; }
		if (region_y < 0.0f) { region_y = 0.0f; }
		else if (region_y > imageSize.y - region_sz) { region_y = imageSize.y - region_sz; }

		ImVec2 uv0 = ImVec2((region_x) / imageSize.x, (region_y) / imageSize.y);
		ImVec2 uv1 = ImVec2((region_x + region_sz) / imageSize.x, (region_y + region_sz) / imageSize.y);
		ImGui::Image(playerID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
		ImGui::EndTooltip();
	}

	ImGui::Text("ID: 2 - Mummy");
	ImGui::Image(mummyID, ImVec2(96, 128), uv_min, uv_max, tint_col, border_col);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float region_sz = 64.0f;
		float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
		float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
		float zoom = 4.0f;

		imageSize = ImVec2(48, 64);


		if (region_x < 0.0f) { region_x = 0.0f; }
		else if (region_x > imageSize.x - region_sz) { region_x = imageSize.x - region_sz; }
		if (region_y < 0.0f) { region_y = 0.0f; }
		else if (region_y > imageSize.y - region_sz) { region_y = imageSize.y - region_sz; }

		ImVec2 uv0 = ImVec2((region_x) / imageSize.x, (region_y) / imageSize.y);
		ImVec2 uv1 = ImVec2((region_x + region_sz) / imageSize.x, (region_y + region_sz) / imageSize.y);
		ImGui::Image(mummyID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
		ImGui::EndTooltip();
	}

	ImGui::Text("ID: 3 - Chest");
	ImGui::Image(chestID, ImVec2(128, 64), uv_min, uv_max, tint_col, border_col);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float region_sz = 64.0f;
		float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
		float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
		float zoom = 4.0f;

		imageSize = ImVec2(64, 32);


		if (region_x < 0.0f) { region_x = 0.0f; }
		else if (region_x > imageSize.x - region_sz) { region_x = imageSize.x - region_sz; }
		if (region_y < 0.0f) { region_y = 0.0f; }
		else if (region_y > imageSize.y - region_sz) { region_y = imageSize.y - region_sz; }

		ImVec2 uv0 = ImVec2((region_x) / imageSize.x, (region_y) / imageSize.y);
		ImVec2 uv1 = ImVec2((region_x + region_sz) / imageSize.x, (region_y + region_sz) / imageSize.y);
		ImGui::Image(chestID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
		ImGui::EndTooltip();
	}

	ImGui::Text("ID: 4 - Door");
	ImGui::Image(ImTextureID(0), ImVec2(128, 64), uv_min, uv_max, tint_col, border_col);


	ImGui::Text("ID: 5 - Anubis");
	ImGui::Image(ImTextureID(anubisID), ImVec2(128, 128), uv_min, uv_max, tint_col, border_col);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float region_sz = 64.0f;
		float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
		float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
		float zoom = 4.0f;

		imageSize = ImVec2(64, 64);


		if (region_x < 0.0f) { region_x = 0.0f; }
		else if (region_x > imageSize.x - region_sz) { region_x = imageSize.x - region_sz; }
		if (region_y < 0.0f) { region_y = 0.0f; }
		else if (region_y > imageSize.y - region_sz) { region_y = imageSize.y - region_sz; }

		ImVec2 uv0 = ImVec2((region_x) / imageSize.x, (region_y) / imageSize.y);
		ImVec2 uv1 = ImVec2((region_x + region_sz) / imageSize.x, (region_y + region_sz) / imageSize.y);
		ImGui::Image(anubisID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
		ImGui::EndTooltip();
	}

	ImGui::Text("ID: 6 - Laser");
	ImGui::Image(ImTextureID(laserID), ImVec2(128, 128), uv_min, uv_max, tint_col, border_col);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float region_sz = 64.0f;
		float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
		float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
		float zoom = 4.0f;

		imageSize = ImVec2(64, 64);


		if (region_x < 0.0f) { region_x = 0.0f; }
		else if (region_x > imageSize.x - region_sz) { region_x = imageSize.x - region_sz; }
		if (region_y < 0.0f) { region_y = 0.0f; }
		else if (region_y > imageSize.y - region_sz) { region_y = imageSize.y - region_sz; }

		ImVec2 uv0 = ImVec2((region_x) / imageSize.x, (region_y) / imageSize.y);
		ImVec2 uv1 = ImVec2((region_x + region_sz) / imageSize.x, (region_y + region_sz) / imageSize.y);
		ImGui::Image(laserID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
		ImGui::EndTooltip();
	}
	
}

void StartRoomMaker(bool& isActive)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(io.DisplaySize);

	if (ImGui::Begin("Room Maker", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings)) {
		Hudson::Common::ResourceManager* resManager = Hudson::Common::ResourceManager::GetInstance();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::BeginMenu("Open")) {
					ImGui::InputTextWithHint("Open Name", ".room", openFileName, IM_ARRAYSIZE(openFileName));
					ImGui::Separator();
					if (ImGui::Button("Open"))
					{
						imguiRoomData.openFromFile(openFileName);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Save")) {

					ImGui::InputTextWithHint("Save Name", ".room", saveFileName, IM_ARRAYSIZE(saveFileName));
					ImGui::Separator();
					if (ImGui::Button("Save"))
					{
						imguiRoomData.saveToFile(saveFileName);
					}
					ImGui::EndMenu();

				}
				if (ImGui::MenuItem("Exit"))
				{
					isActive = false;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		if (ImGui::BeginChild("Room Editor", ImVec2((io.DisplaySize.x / 3 * 2) - io.DisplaySize.x * 0.02f, 0), true, ImGuiWindowFlags_HorizontalScrollbar)) {
			ImGui::Text("Room Editor");
			ImGui::Separator();

			if (ImGui::SliderInt("Room Size X", &imguiRoomData.roomX, 10, 25)) {
				imguiRoomData.updateRoomSize(imguiRoomData.roomX, imguiRoomData.roomY);
			}
			if (ImGui::SliderInt("Room Size Y", &imguiRoomData.roomY, 8, 14)) {
				imguiRoomData.updateRoomSize(imguiRoomData.roomX, imguiRoomData.roomY);
			}

			for (int y = 0; y < imguiRoomData.roomY; ++y) {
				for (int x = 0; x < imguiRoomData.roomX; ++x) {
					if (x > 0)
						ImGui::SameLine();
					ImGui::PushID(y * 4 + x);

					stringstream ss;
					ss << x;
					ss << ",";
					ss << y;
					string str = ss.str();

					if (ImGui::Selectable(str.c_str(), imguiRoomData.selected == &imguiRoomData.roomGrid[y * imguiRoomData.roomX + x], 0, ImVec2(30, 30)))
					{
						imguiRoomData.selected = &imguiRoomData.roomGrid[y * imguiRoomData.roomX + x];
					}
					ImGui::PopID();
				}
			}
			ImGui::Text("Room Overview");
			ImGui::Separator();


			ImGui::EndChild();
			ImGui::PopStyleVar();

		}

		ImGui::SameLine();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		if (ImGui::BeginChild("Functionality", ImVec2(io.DisplaySize.x / 3, 0), true)) {

			if (imguiRoomData.selected != nullptr) {

				ImGui::Text("Tile Editor");
				ImGui::Separator();

				ImGui::Checkbox("isSolid?", &imguiRoomData.selected->isSolid);
				ImGui::InputInt("Texture Reference", &imguiRoomData.selected->textureRef);
				ImGui::InputInt("Object Reference", &imguiRoomData.selected->objectRef);
			}

			ImGui::Text("Texture References");
			ImGui::Separator();

			for (textureRefData* textureRef : imguiRoomData.textureRefs) // access by reference to avoid copying
			{
				Hudson::Render::Texture* relevantTex = resManager->GetTexture(textureRef->textureRoot);
				if (resManager->GetTexture(textureRef->textureRoot) == nullptr) {
					relevantTex = resManager->LoadTexture(textureRef->textureRoot, true, textureRef->textureRoot);
				}

				ImTextureID textureID = reinterpret_cast<ImTextureID>(relevantTex->ID);
				ImVec2 pos = ImGui::GetCursorScreenPos();

				ImVec2 imageSize = ImVec2(128, 128);
				ImVec2 uv_min = ImVec2(1.0f, 0.0f); // Top-left
				ImVec2 uv_max = ImVec2(0.0f, 1.0f); // Lower-right
				ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
				ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

				ImGui::PushID(textureRef);

				ImGui::Image(textureID, ImVec2(96, 128), uv_min, uv_max, tint_col, border_col);
				if (ImGui::IsItemHovered())
				{
					if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
						ImGui::OpenPopup("Texture Options");
					}

					ImGui::BeginTooltip();
					float region_sz = 64.0f;
					float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
					float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
					float zoom = 4.0f;

					imageSize = ImVec2(48, 64);

					if (region_x < 0.0f) { region_x = 0.0f; }
					else if (region_x > imageSize.x - region_sz) { region_x = imageSize.x - region_sz; }
					if (region_y < 0.0f) { region_y = 0.0f; }
					else if (region_y > imageSize.y - region_sz) { region_y = imageSize.y - region_sz; }

					ImVec2 uv0 = ImVec2((region_x) / imageSize.x, (region_y) / imageSize.y);
					ImVec2 uv1 = ImVec2((region_x + region_sz) / imageSize.x, (region_y + region_sz) / imageSize.y);
					ImGui::Image(textureID, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);

					ImGui::Text("textureID: %.1f", (float)textureRef->textureID);
					ImGui::Text("textureRoot: %s", textureRef->textureRoot.c_str());
					ImGui::Text("gridSizeX: %.1f", (float)textureRef->gridSizeX);
					ImGui::Text("gridSizeY: %.1f", (float)textureRef->gridSizeY);
					ImGui::Text("gridPosX: %.1f", (float)textureRef->gridPosX);
					ImGui::Text("gridPosY: %.1f", (float)textureRef->gridPosY);
					ImGui::Text("Right click for more options");
					ImGui::EndTooltip();
				}

				if (ImGui::BeginPopup("Texture Options")) {

					if (ImGui::Button("Delete")) {

						auto it = find(imguiRoomData.textureRefs.begin(), imguiRoomData.textureRefs.end(), textureRef);
						if (it != imguiRoomData.textureRefs.end())
						{
							int index = it - imguiRoomData.textureRefs.begin();
							imguiRoomData.textureRefs.erase(imguiRoomData.textureRefs.begin() + index);
						}

						ImGui::CloseCurrentPopup();
					}
					ImGui::Separator();
					if (ImGui::Button("Dismiss")) {
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}
				ImGui::PopID();
			}

			if (addingTextureRef) {

				ImGui::InputText("Texture Root", &newRefData.textureRoot);
				ImGui::InputInt("Texture ID", &newRefData.textureID);
				ImGui::InputInt("Grid Size X", &newRefData.gridSizeX);
				ImGui::InputInt("Grid Size Y", &newRefData.gridSizeY);
				ImGui::InputInt("Grid Pos X", &newRefData.gridPosX);
				ImGui::InputInt("Grid Pos Y", &newRefData.gridPosY);

				if (ImGui::Button("Save", ImVec2(ImGui::GetWindowSize().x, 0))) {
					textureRefData* copyRefData = new textureRefData();
					copyRefData->textureID = newRefData.textureID;
					copyRefData->textureRoot = newRefData.textureRoot;
					copyRefData->gridSizeX = newRefData.gridSizeX;
					copyRefData->gridSizeY = newRefData.gridSizeY;
					copyRefData->gridPosX = newRefData.gridPosX;
					copyRefData->gridPosY = newRefData.gridPosY;

					imguiRoomData.textureRefs.push_back(copyRefData);
					resManager->LoadTexture(copyRefData->textureRoot, true, copyRefData->textureRoot);
					addingTextureRef = false;

				}
				if (ImGui::Button("Discard", ImVec2(ImGui::GetWindowSize().x, 0))) {
					addingTextureRef = false;
				}
			}
			else {
				if (ImGui::Button("+", ImVec2(ImGui::GetWindowSize().x, 0))) {
					newRefData.Clear();
					addingTextureRef = true;
				}
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text("Add new texture");
					ImGui::EndTooltip();
				}
			}

			ImGui::Text("Object References");
			ImGui::Separator();
			ObjectList();


			ImGui::EndChild();
			ImGui::PopStyleVar();
		}

		ImGui::End();
	}

}
