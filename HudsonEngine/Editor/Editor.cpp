#include "../Editor/Editor.h"
#include "../Common/Engine.h"

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

