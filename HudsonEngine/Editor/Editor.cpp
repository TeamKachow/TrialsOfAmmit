#include "../Editor/Editor.h"
#include "../Common/Engine.h"
#include "../Render/Renderer.h"
#include "../Render/Window.h"

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

void Hudson::Editor::Editor::Scene()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Scene");
	//ImGui::Scale
	ImTextureID textureID = reinterpret_cast<ImTextureID>(_engine->GetRenderer()->GetRenderedSceneTexture());

	// TODO take an Unreal approach and make it so that the image caps at a certain size
	ImVec2 imageSize = { ImGui::GetContentRegionMax().x,ImGui::GetContentRegionMax().y };

	ImVec2 uv_min = ImVec2(1.0f, 1.0f); // Top-left
	ImVec2 uv_max = ImVec2(0.0f, 0.0f); // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

	ImGui::Image(textureID, imageSize, uv_min, uv_max, tint_col, border_col);

	// TODO clean this up, doesnt need to run every frame but testing for now
	// TODO detect a change easy enough
	if(ImGui::GetContentRegionMax().x > 0 && ImGui::GetContentRegionMax().y > 0)
	{
		// Framebuffer can't have 0 or less so, this queues framebuffer recreate for when the application isnt minimized
		_engine->GetRenderer()->CreateFramebuffers(ImGui::GetContentRegionMax().x, ImGui::GetContentRegionMax().y);
	}

	ImGui::End();
	ImGui::PopStyleVar();
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
	Scene();
	Hierarchy();
	ContentBrowser();
	ComponentList();
	ObjectComponents();
	Tools();
	Debug();
}

