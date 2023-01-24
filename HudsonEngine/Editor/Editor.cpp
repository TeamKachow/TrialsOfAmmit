#include "../Editor/Editor.h"
#include "../Common/Engine.h"
#include "../Entity/Component.h"
#include "../Entity/GameObject.h"
#include "../World/Scene.h"

constexpr ImVec4 IM_COLOR_GRAY		= { 0.7f, 0.7f, 0.7f, 1.0f };
constexpr ImVec4 IM_COLOR_ORANGE	= { 1.0f, 0.8f, 0.0f, 1.0f };

Hudson::Editor::Editor::Editor(Common::Engine* engine, ComponentRegistry* registry) : _engine(engine), _registry(registry)
{
	engine->RegisterFrameHook([this](Common::Engine* engine)
		{
			this->Draw();
		});
}

Hudson::Editor::Editor::~Editor()
{

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
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("File"))
			{

			}
			if (ImGui::MenuItem("Inputs"))
			{

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

		if (ImGui::BeginMenu("Debug"))
		{
			ImGui::MenuItem("Show IDs", "", &_showIds);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
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
		    for (auto object : scene->GetObjects())
            {
				ImGuiTreeNodeFlags objNodeFlags = ImGuiTreeNodeFlags_Leaf;
				if (_selected == object)
				{
					objNodeFlags |= ImGuiTreeNodeFlags_Selected;
				}
				ImGui::TreeNodeEx((void*)(intptr_t)j, objNodeFlags, "(%d) %s", j, object->GetName().c_str());
				ImGui::TreePop();
				if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
				{
					_selected = object;
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

void Hudson::Editor::Editor::ContentBrowser()
{
	ImGui::Begin("Content Browser");

	ImGui::TextColored(IM_COLOR_GRAY, "Not yet implemented");

	ImGui::End();
}

void Hudson::Editor::Editor::ComponentList()
{
	ImGui::Begin("Components List");

	if (_registry)
	{
		if (_registry->GetKnownComponents().empty())
		{
			ImGui::TextColored(IM_COLOR_ORANGE, "No components registered!");
		}
		else if (_selected == nullptr)
		{
			ImGui::TextColored(IM_COLOR_GRAY, "Select an object from Hierarchy.");
		}
		else
		{
			ImGui::TextColored(IM_COLOR_GRAY, "Select a component below to add.");

			for (auto element : _registry->GetKnownComponents())
			{
				ImGui::Text(element.name.c_str());
				ImGui::SameLine();
				ImGui::PushID((void*)(&element.constructor));
				if (ImGui::SmallButton("+"))
				{
					// Add the component
					auto component = element.constructor();
					_selected->AddComponent(component);
					std::cout << "Would add a " << element.name << " right now\n";
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

void Hudson::Editor::Editor::ObjectComponents()
{
	ImGui::Begin("Object Components");

	if (_selected == nullptr)
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
			ImGui::InputText("", &_selected->GetName());
			ImGui::PopID();
		    ImGui::TableNextColumn();

			if (_showIds)
			{
				ImGui::Text("Runtime ID (?)");
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("The runtime ID (pointer) is logged in debug messages.");
				ImGui::TableNextColumn();

				ImGui::Text("%p", (void*)_selected);
				ImGui::TableNextColumn();

				ImGui::Text("Serial ID (?)");
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("The serial ID is stored in .scene files. (WIP)");
				ImGui::TableNextColumn();

				ImGui::Text("%u", /*_selected.GetSerialID()*/ 0); // TODO
			}

			ImGui::EndTable();
		}

        for (auto component : _selected->GetAllComponents())
        {
			ImGui::PushID((void*)component);
			if (ImGui::CollapsingHeader(component->GetName()))
			{
				if (_showIds)
				{
					if (ImGui::BeginTable("CompEditor", 2, ImGuiTableFlags_Resizable))
				    {
						ImGui::TableNextColumn();
						ImGui::Text("Runtime ID (?)");
						if (ImGui::IsItemHovered()) ImGui::SetTooltip("The runtime ID (pointer) is logged in debug messages.");
						ImGui::TableNextColumn();

						ImGui::Text("%p", (void*)_selected);
						ImGui::TableNextColumn();

						ImGui::Text("Serial ID (?)");
						if (ImGui::IsItemHovered()) ImGui::SetTooltip("The serial ID is stored in .scene files. (WIP)");
						ImGui::TableNextColumn();

						ImGui::Text("%u", /*_selected.GetSerialID()*/ 0); // TODO
						ImGui::EndTable();
					}
				}

				Common::IEditable* editable = dynamic_cast<Common::IEditable*>(component);
				if (editable)
				{
					editable->DrawPropertyUI();
				}
				else
				{
					ImGui::TextColored(IM_COLOR_GRAY, "Component is not editable");
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

void Hudson::Editor::Editor::Draw()
{
	MenuBar();
	Hierarchy();
	ContentBrowser();
	ComponentList();
	ObjectComponents();
	Tools();
	Debug();
}

