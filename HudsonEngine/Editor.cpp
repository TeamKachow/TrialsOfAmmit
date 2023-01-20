#include "Editor.h"
#include "Common/Engine.h"

Hudson::Editor::Editor::Editor(Common::Engine* engine) : _engine(engine)
{
	engine->RegisterFrameHook([this](Common::Engine* engine)
	{
			this->Draw();
	});
}

Hudson::Editor::Editor::~Editor()
{

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
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Hudson::Editor::Editor::Hierarchy()
{
	ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_MenuBar);


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

