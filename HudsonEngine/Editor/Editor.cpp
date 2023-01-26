#include "../Editor/Editor.h"
#include "../Common/Engine.h"

Hudson::Editor::Editor::Editor(Common::Engine* engine) : _engine(engine)
{
	openInput = false;
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
		ImGui::EndMainMenuBar();
	}
}

void Hudson::Editor::Editor::Hierarchy()
{
	ImGui::Begin("Hierarchy");
	ImGui::End();
}

void Hudson::Editor::Editor::ContentBrowser()
{

	ImGui::Begin("Content Browser");
	ImGui::End();
}

void Hudson::Editor::Editor::ComponentList()
{
	ImGui::Begin("Components List");
	ImGui::End();
}

void Hudson::Editor::Editor::ObjectComponents()
{
	ImGui::Begin("Object Components");
	ImGui::End();
}

void Hudson::Editor::Editor::Tools()
{

	ImGui::Begin("Tools");
	ImGui::End();
}

void Hudson::Editor::Editor::Debug()
{
	ImGui::Begin("Debug");
	ImGui::End();
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
		const char* listbox_items[] = { "Spacebar", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
										"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Escape", "Right", "Left", "Down", "Up" };

		static int listbox_item_current = -1, listbox_item_current2 = -1;
		ImGui::ListBox("##KeyMapping", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
		ImGui::Text("Selected Key:"); ImGui::SameLine();
		if (listbox_item_current > -1)
		{
			ImGui::Text(listbox_items[listbox_item_current]);
			strcpy_s(keyAction, _engine->GetInputManager()->getAction(listbox_items[listbox_item_current]).c_str());
		}
		else
			ImGui::Text("None Selected");
		ImGui::Text("Action: "); ImGui::SameLine();
		if (ImGui::InputText("##Action", keyAction, sizeof(keyAction), ImGuiInputTextFlags_EnterReturnsTrue))
			_engine->GetInputManager()->setKeyEvent(std::string(keyAction), std::string(listbox_items[listbox_item_current]));
		if (ImGui::Button("Unassign"))
			_engine->GetInputManager()->setKeyEvent("Not Assigned", std::string(listbox_items[listbox_item_current]));
		ImGui::PushItemWidth(-1);
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Controller Mapping(Soon):");
		ImGui::ListBox("##listbox2", &listbox_item_current2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
		ImGui::End();
	}
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
	if (openInput)
		Input();
}

