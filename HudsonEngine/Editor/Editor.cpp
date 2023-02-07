#include "Editor.h"
#include "../Common/Engine.h"
#include "../Common/ComponentRegistry.h"
#include "../Entity/Component.h"
#include "../Entity/GameObject.h"
#include "../World/Scene.h"
#include "../Render/Renderer.h"
#include "../Util/Debug.h"

constexpr ImVec4 IM_COLOR_GRAY = { 0.7f, 0.7f, 0.7f, 1.0f };
constexpr ImVec4 IM_COLOR_ORANGE = { 1.0f, 0.8f, 0.0f, 1.0f };

const char* MODAL_HELP = "'How to Hudson', a memoir by best-selling author Doc Hudson";
const char* MODAL_SCENE_SAVE = "Save Scene";
const char* MODAL_SCENE_LOAD = "Load Scene";

static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstring_converter;

extern const std::filesystem::path filePath = std::filesystem::current_path();

Hudson::Editor::Editor::Editor(Common::Engine* engine) : _engine(engine), currentPath(filePath)
{
	engine->RegisterPreFrameHook([&](Common::Engine* engine)
		{
			engine->GetRenderer()->SetImguiDockspace(true);
		    if (!engine->GetSceneManager()->IsPaused())
		    {
                for (SceneMeta& meta : _sceneMeta | std::views::values)
                {
					meta.pendingChanges = true;
                }
		    }
		});

	engine->RegisterMidFrameHook([&](Common::Engine* engine)
		{
			this->Draw();
		});
}

Hudson::Editor::Editor::~Editor()
{

}

bool Hudson::Editor::Editor::LoadImGuiImage(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	//	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	//#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}

void Hudson::Editor::Editor::InfiniteButton()
{
	if (ImGui::BeginMenu("Make Engine"))
	{
		ImGui::MenuItem("Load Components...");
		ImGui::MenuItem("Load Engine Stuff...");

		if (ImGui::BeginMenu("Make Game"))
		{
			ImGui::MenuItem("The Motor Speedway of the South");
			ImGui::MenuItem("Some Sort of Roguelike");
			ImGui::MenuItem("Black Ops 2 - Remastered");
			ImGui::MenuItem("Half-Life 3");

			if (ImGui::BeginMenu("Finish Game..."))
			{
				InfiniteButton();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void Hudson::Editor::Editor::MenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Very Useful Menu"))
		{
			if (ImGui::MenuItem("File"))
			{

			}
			if (ImGui::MenuItem("Inputs"))
			{
				openInput = true;
			}

			if (ImGui::BeginMenu("Build"))
			{
				ImGui::MenuItem("Doc Hudson");
				ImGui::MenuItem("Lightning McQueen");
				ImGui::MenuItem("Chick Hicks");

				if (ImGui::BeginMenu("More..."))
				{
					ImGui::MenuItem("Tow Mater");
					ImGui::MenuItem("Strip Weathers");

					if (ImGui::BeginMenu("Even More..."))
					{
						InfiniteButton();
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		ImGui::Separator();

		if (ImGui::BeginMenu("Scenes"))
		{
			if (ImGui::MenuItem("New Empty Scene"))
			{
				_engine->GetSceneManager()->AddScene(new World::Scene());
			}
			ImGui::MenuItem("Load Scene...", 0, false, false);
			if (ImGui::MenuItem("Save All..."))
			{
			    // TODO: save all scenes
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Debug"))
		{
			ImGui::MenuItem("Show IDs", "", &_showIds);
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Help", 0, &_showHelp));

		ImGui::Separator();

		if (ImGui::MenuItem("Play", 0, !_engine->GetSceneManager()->IsPaused(), _engine->GetSceneManager()->IsPaused()))
		{
			// TODO: force all scenes to save first!!!
			_engine->GetSceneManager()->SetPaused(false);
		}

		if (ImGui::MenuItem("Pause", 0, _engine->GetSceneManager()->IsPaused(), !_engine->GetSceneManager()->IsPaused()))
		{
			_engine->GetSceneManager()->SetPaused(true);
		}

		ImGui::EndMainMenuBar();
	}
}

void Hudson::Editor::Editor::Scene()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoScrollbar);
	//ImGui::Scale
	ImTextureID textureID = reinterpret_cast<ImTextureID>(_engine->GetRenderer()->GetRenderedSceneTexture());

	// TODO take an Unreal approach and make it so that the image caps at a certain size
	ImVec2 imageSize = { ImGui::GetContentRegionAvail().x,ImGui::GetContentRegionAvail().y };

	ImVec2 uv_min = ImVec2(0.0f, 1.0f); // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 0.0f); // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

	ImGui::Image(textureID, imageSize, uv_min, uv_max, tint_col, border_col);

	// TODO clean this up, doesnt need to run every frame but testing for now
	// TODO detect a change easy enough
	if (imageSize.x > 0 && imageSize.y > 0)
	{
		// Framebuffer can't have 0 or less so, this queues framebuffer recreate for when the application isnt minimized
		_engine->GetRenderer()->CreateFramebuffers(imageSize.x, imageSize.y);
	}

	ImGui::End();
	ImGui::PopStyleVar();
}

Hudson::Editor::Editor::SceneMeta& Hudson::Editor::Editor::GetSceneMeta(World::Scene* scene)
{
	if (!_sceneMeta.contains(scene))
	{
		_sceneMeta.insert_or_assign(scene, SceneMeta());
	}

	return _sceneMeta[scene];
}

void Hudson::Editor::Editor::ShowSceneSaveAs(World::Scene* scene)
{
	_sceneToSave = scene;
}

void Hudson::Editor::Editor::Hierarchy()
{
	ImGui::Begin("Hierarchy");

	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	int i = 0, j = 0;
	for (auto scene : scenes)
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);

		if (ImGui::TreeNode((void*)(intptr_t)i, "Scene %d - %s", i, scene->GetName().c_str()))
		{
			if (ImGui::BeginPopupContextItem())
			{
				ImGui::PushID(&scene);
				ImGui::InputText("", &scene->_name);
				ImGui::PopID();
				ImGui::Separator();
				if (ImGui::MenuItem("Active?", 0, scene->IsActive()))
				{
					scene->SetActive(!scene->IsActive());
				}
				if (ImGui::MenuItem("Rendering?", 0, scene->IsRendering()))
				{
					scene->SetRendering(!scene->IsRendering());
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Create Empty Object"))
				{
					scene->AddObject(new Entity::GameObject());
				}
				if (ImGui::MenuItem("Paste Object", 0, false, false))
				{
					// TODO: object/component clipboard
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Save Scene", 0, false, !GetSceneMeta(scene).filePath.empty()))
				{
					SceneMeta& meta = GetSceneMeta(scene);
					if (meta.filePath.empty())
					{
						ShowSceneSaveAs(scene);
					}
					else
					{
						World::SceneManager::SaveScene(meta.filePath, scene);
					}
				}
				if (ImGui::MenuItem("Save Scene As..."))
				{
					ShowSceneSaveAs(scene);
				}
				if (ImGui::MenuItem("Duplicate Scene", 0, false, false))
				{
				}
				if (ImGui::MenuItem("Delete Scene (!)"))
				{
					_selectedObj = nullptr;
					_engine->GetSceneManager()->RemoveScene(scene);
				}
				ImGui::EndPopup();
			}

			SceneMeta& meta = GetSceneMeta(scene);
			std::stringstream txt;
			if (meta.filePath.empty())
			{
				txt << "(not saved)";
			}
			else
			{
				txt << meta.filePath;
				if (meta.pendingChanges)
				{
					txt << " (edited)";
				}
			}
			ImGui::TextColored(IM_COLOR_GRAY, txt.str().c_str());

		    for (auto object : scene->GetObjects())
            {
				ImGuiTreeNodeFlags objNodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet;
				if (_selectedObj == object)
				{
					objNodeFlags |= ImGuiTreeNodeFlags_Selected;
				}
				ImGui::TreeNodeEx((void*)(intptr_t)j, objNodeFlags, "(%d) %s", j, object->GetName().c_str());
				ImGui::TreePop();
				if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
				{
					_selectedObj = object;
				}
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Save Object...", 0, false, false))
					{
						// TODO: save
					}
					if (ImGui::MenuItem("Copy Object", 0, false, false))
					{
						// TODO: copy
					}
					if (ImGui::MenuItem("Delete Object"))
					{
						ImGui::CloseCurrentPopup();
						if (_selectedObj == object)
						{
							_selectedObj = nullptr;
						}
						scene->RemoveObject(object);
					}
					ImGui::EndPopup();
				}
				++j;
			}
			ImGui::TreePop();
		}

		j = 0;
		++i;
	}

	ImGui::End();
}

//const char* contentDirectory = "DemoGame";
void Hudson::Editor::Editor::ContentBrowser()
{
	static bool image1 = LoadImGuiImage("../DemoGame/textures/DirectoryIcon.png", &directoryIcon, &my_image_width, &my_image_height);
	static bool image2 = LoadImGuiImage("../DemoGame/textures/FileIcon.png", &fileIcon, &my_image_width, &my_image_height);

	ImGui::Begin("Content Browser");

	if (!std::filesystem::equivalent(filePath, currentPath))
	{
		if (ImGui::Button("<--"))
		{
			currentPath = currentPath.parent_path();
		}
	}

	ImGui::SameLine();
	ImGui::Text(currentPath.string().c_str());

	float padding = 16.0f;
	float thumbnailSize = 64.0f;
	float cellSize = thumbnailSize + padding;

	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
	{
		columnCount = 1;
	}

	ImGui::Columns(columnCount, 0, false);

	// Loops over every file path

	int i = 0;
	for (auto& entry : std::filesystem::directory_iterator(currentPath))
	{
		ImGui::PushID(i++);

		const std::filesystem::path& path = entry.path();
		std::filesystem::path relativePath; relativePath = std::filesystem::relative(entry.path(), filePath);
		std::string filenameString = relativePath.filename().string();

		auto icon = entry.is_directory() ? directoryIcon : fileIcon;

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::ImageButton((ImTextureID)icon, {thumbnailSize, thumbnailSize}, {0,1}, {1,0});
		ImGui::PopStyleColor();

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			const wchar_t* contentPath = relativePath.c_str();
			ImGui::SetDragDropPayload("ContentItem", contentPath, (wcslen(contentPath) + 1) * sizeof(wchar_t));
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (entry.is_directory())
			{
				currentPath /= path.filename();
			}
			else if (entry.is_regular_file() && entry.path().string().ends_with(".scene.json"))
			{
				_sceneToLoad = std::filesystem::relative(entry.path()).string();
			}
			std::cout << relativePath.string() << std::endl;
		}

		ImGui::TextWrapped(filenameString.c_str());

		ImGui::NextColumn();

		ImGui::PopID();
	}
	ImGui::Columns(1);

	ImGui::End();
}

void Hudson::Editor::Editor::ComponentList()
{
	Hudson::Common::ComponentRegistry* registry = _engine->GetComponentRegistry();

	ImGui::Begin("Components List");

	if (registry)
	{
		if (registry->GetKnownComponents().empty())
		{
			ImGui::TextColored(IM_COLOR_ORANGE, "No components registered!");
		}
		else if (_selectedObj == nullptr)
		{
			ImGui::TextColored(IM_COLOR_GRAY, "Select an object from Hierarchy.");
		}
		else
		{
			ImGui::TextColored(IM_COLOR_GRAY, "Select a component below to add.");

			for (auto& [name, entry] : registry->GetKnownComponents())
			{
				ImGui::Text(name.c_str());
				ImGui::SameLine();
				ImGui::PushID((void*)(&entry));
				if (ImGui::SmallButton("+"))
				{
					// Add the component
					auto component = entry.constructor();
					_selectedObj->AddComponent(component);
				}
				ImGui::PopID();
			}

		}
	}
	else
	{
		ImGui::TextColored(IM_COLOR_ORANGE, "No ComponentRegistry found!");
	}

	ImGui::End();
}

void Hudson::Editor::Editor::ObjectProperties()
{
	ImGui::Begin("Object Properties");

	if (_selectedObj == nullptr)
	{
		ImGui::TextColored(IM_COLOR_GRAY, "Select an object from Hierarchy.");
	}
	else
	{
		if (ImGui::BeginTable("ObjEditor", 2, ImGuiTableFlags_Resizable))
		{
			ImGui::TableNextColumn();

			ImGui::Text("Name");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Rename");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::InputText("", &_selectedObj->GetName());
			ImGui::PopID();
			ImGui::TableNextColumn();

			if (_showIds)
			{
				ImGui::Text("Runtime ID (?)");
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("The runtime ID (pointer) is logged in debug messages.");
				ImGui::TableNextColumn();

				ImGui::Text("%p", (void*)_selectedObj);
				ImGui::TableNextColumn();

				ImGui::Text("Serial ID (?)");
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("The serial ID is stored in .scene files. (WIP)");
				ImGui::TableNextColumn();

				ImGui::Text("%u", _selectedObj->GetSerialID());
				ImGui::TableNextColumn();
			}

			ImGui::Text("Position");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Pos");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::DragFloat2("", &_selectedObj->GetTransform().pos.x, 0.5f);
			ImGui::PopID();
			ImGui::TableNextColumn();

			ImGui::Text("Scale");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Scale");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::DragFloat2("", &_selectedObj->GetTransform().scale.x, 0.5f);
			ImGui::PopID();
			ImGui::TableNextColumn();

			ImGui::Text("Rotation");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Rotate");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::DragFloat("", &_selectedObj->GetTransform().rotateZ, 0.5f);
			ImGui::PopID();
			ImGui::TableNextColumn();

			ImGui::EndTable();
		}

        for (auto component : _selectedObj->GetAllComponents())
        {
			Common::IEditable* editable = dynamic_cast<Common::IEditable*>(component);
			ImGuiTreeNodeFlags headerFlags = 0;
			if (!editable && !_showIds)
				headerFlags |= ImGuiTreeNodeFlags_Leaf;

			ImGui::PushID((void*)component);
			bool compOpen = ImGui::CollapsingHeader(component->GetTypeName(), headerFlags);
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Copy Component...", 0, false, false))
				{
					// TODO
				}
				if (ImGui::MenuItem("Delete Component"))
				{
					component->GetParent()->RemoveComponent(component);
				}
				ImGui::EndPopup();
			}
			if (compOpen)
			{
				if (_showIds)
				{
					if (ImGui::BeginTable("CompEditor", 2, ImGuiTableFlags_Resizable))
					{
						ImGui::TableNextColumn();
						ImGui::Text("Runtime ID (?)");
						if (ImGui::IsItemHovered()) ImGui::SetTooltip("The runtime ID (pointer) is logged in debug messages.");
						ImGui::TableNextColumn();

						ImGui::Text("%p", (void*)_selectedObj);
						ImGui::TableNextColumn();

						ImGui::Text("Serial ID (?)");
						if (ImGui::IsItemHovered()) ImGui::SetTooltip("The serial ID is stored in .scene files. (WIP)");
						ImGui::TableNextColumn();

						ImGui::Text("%u", _selectedObj->GetSerialID()); // TODO
						ImGui::EndTable();
					}
				}

				if (editable)
				{
					editable->DrawPropertyUI();
				}
			}
			ImGui::PopID();
		}
	}

	ImGui::End();
}

void Hudson::Editor::Editor::Tools()
{
	ImGui::Begin("Tools");
	ImGui::TextColored(IM_COLOR_GRAY, "Not yet implemented");
	ImGui::End();
}

void Hudson::Editor::Editor::Debug()
{
	ImGui::Begin("Debug");
	ImGui::TextColored(IM_COLOR_GRAY, "Not yet implemented");
	ImGui::End();
}

void Hudson::Editor::Editor::Help()
{
	if (ImGui::BeginPopupModal(MODAL_HELP, &_showHelp))
	{
		ImGui::Text("Just try right-clicking things to see what menus exist");
		ImGui::Text("The end");

		ImGui::EndPopup();
	}

	if (_showHelp)
	{
		ImGui::OpenPopup(MODAL_HELP);
	}
}

void Hudson::Editor::Editor::Input()
{
	if (!ImGui::Begin("Input Manager", &openInput))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Key Mapping: ");
		const char* listbox_keyNames[] = { "Spacebar", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
										"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Escape", "Right", "Left", "Down", "Up" };
		static int listbox_keyNames_current = -1;
		static int listbox_keyActions_current = -1;
		std::vector<Action> actionItems;
		ImGui::PushItemWidth(100.0f);
		ImGui::ListBox("##KeyMapping", &listbox_keyNames_current, listbox_keyNames, IM_ARRAYSIZE(listbox_keyNames), 4);
		ImGui::Text("Selected Key:"); ImGui::SameLine();
		if (listbox_keyNames_current > -1)
		{
			ImGui::Text(listbox_keyNames[listbox_keyNames_current]);
			ImGui::Text("Key Actions:");
			std::vector<std::string> keyActions = _engine->GetInputManager()->getKeyActions(listbox_keyNames[listbox_keyNames_current]);
			for (std::string& tempActionName : keyActions)
			{
				Action tempAction;
				tempAction.actionName = tempActionName;
				actionItems.push_back(tempAction);
			}
			int selectionNum = 0;
			ImGui::ListBoxHeader("##KeyActions", ImVec2(100.0f, 75.0f));
			for (int i = 0; i < actionItems.size(); i++)
			{
				const bool itemSelected = (i == listbox_keyActions_current);
				std::string& actionName = actionItems[i].actionName;
				if (ImGui::Selectable(actionName.c_str(), itemSelected))
				{
					listbox_keyActions_current = i;
				}
			}
			ImGui::ListBoxFooter();

			ImGui::Text("Set Action: "); ImGui::SameLine();
			if (ImGui::InputText("##Action", keyAction, sizeof(keyAction), ImGuiInputTextFlags_EnterReturnsTrue))
			{
				_engine->GetInputManager()->setKeyEvent(std::string(keyAction), std::string(listbox_keyNames[listbox_keyNames_current]));
			}
		}
		else
		{
			ImGui::Text("None Selected");
			listbox_keyActions_current = -1;
		}

		if (listbox_keyActions_current > -1)
		{
			if (ImGui::Button("Unassign"))
			{
				_engine->GetInputManager()->delKeyEvent(actionItems[listbox_keyActions_current].actionName, std::string(listbox_keyNames[listbox_keyNames_current]));
			}
		}

		ImGui::PushItemWidth(300.0f);

		if (ImGui::Button("Save Changes"))
		{
			_engine->GetInputManager()->WriteToJSON();
		}
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Controller Mapping(Soon):");
		ImGui::End();
	}
}

void Hudson::Editor::Editor::SaveDialogs()
{
	if (ImGui::BeginPopupModal(MODAL_SCENE_SAVE))
	{
		if (!_sceneToSave)
		{
			_sceneToSave = nullptr;
			ImGui::CloseCurrentPopup();
		}
		else
		{
			ImGui::Text("Save scene '%s' as:", _sceneToSave->GetName().c_str());
			SceneMeta& meta = GetSceneMeta(_sceneToSave);
			if (meta.filePath.empty())
			{
				meta.filePath = std::format("Scenes/{}.scene.json", _sceneToSave->GetName());
			}
			ImGui::InputText("File name", &meta.filePath);
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			ImGui::BeginDisabled(meta.filePath.empty());
			if (ImGui::Button("Save"))
			{
				World::SceneManager::SaveScene(meta.filePath, _sceneToSave);
				meta.pendingChanges = false;
				_sceneToSave = nullptr;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndDisabled();
		}

		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupModal(MODAL_SCENE_LOAD))
	{
		if (_sceneToLoad.empty())
		{
			ImGui::CloseCurrentPopup();
		}
		else
		{
			bool disabled = false;
			if (!_sceneToLoad.ends_with(".scene.json"))
			{
				disabled = true;
				ImGui::TextColored(IM_COLOR_ORANGE, "Scene path not valid. Make sure the file ends with '.scene.json'.");
			}
			else
			{
				ImGui::Text("Load scene '%s'?", _sceneToLoad.c_str());
			}

		    if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			ImGui::BeginDisabled(disabled);
			if (ImGui::Button("Load"))
			{
				try
				{
					World::Scene* loadedScene = World::SceneManager::LoadScene(_sceneToLoad);
					if (!loadedScene)
					{
						throw std::exception("File could not be opened");
					}
					GetSceneMeta(loadedScene) = {
						.pendingChanges = false,
						.filePath = _sceneToLoad,
					};
					_engine->GetSceneManager()->AddScene(loadedScene);
					_sceneToLoad = "";
				}
				catch (std::exception& e)
				{
					std::stringstream msg;
					msg << "Failed to load scene '" << _sceneToLoad << "': " << e.what();
					Hudson::Util::Debug::LogError(msg.str());
					_sceneToLoad = "";
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndDisabled();
		}

		ImGui::EndPopup();
	}


	if (_sceneToSave)
	{
		_engine->GetSceneManager()->SetPaused(true);
		ImGui::OpenPopup(MODAL_SCENE_SAVE);
	}
	else if (!_sceneToLoad.empty())
	{
		_engine->GetSceneManager()->SetPaused(true);
		ImGui::OpenPopup(MODAL_SCENE_LOAD);
	}
}

void Hudson::Editor::Editor::Draw()
{
	MenuBar();
	Scene();
	Hierarchy();
	ContentBrowser();
	ComponentList();
	ObjectProperties();
	Tools();
	Debug();
	Help();
	SaveDialogs();
	if (openInput)
	{
		Input();
	}
}

