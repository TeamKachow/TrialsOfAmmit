#include "Renderer.h"
#include "../Render/Window.h"
#include "../Common/Engine.h"
#include "../Common/ResourceManager.h"
#include "../Entity/GameObject.h"
#include "../Render/SpriteComponent.h"
#include "../World/Scene.h"

Hudson::Render::Renderer::Renderer(Common::Engine* engine) :
	_engine(engine),
	_window(std::make_unique<Window>(1280, 720, "DemoGame (TEMP): Hudson render window")),
	_defaultCamera(0.0f, 1600.0f, 900.0f, 0.0f)


{
	static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window->GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460");


	// VERY VERY TEMPORARY, DO NOT KEEP THIS HERE
	auto resManager = Hudson::Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

	resManager->GetShader("spriteShader")->Use().SetInteger("image", 0);
	resManager->GetShader("spriteShader")->SetMatrix4("projection", _defaultCamera.GetProjectionMatrix());

	// load textures
	resManager->LoadTexture("textures/mummy_texture.png", true, "Mummy");
}

Hudson::Render::Renderer::~Renderer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Hudson::Render::Renderer::StartImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}


void Hudson::Render::Renderer::Draw()
{
	// Clear back buffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO replace with per-scene
	auto resManager = Hudson::Common::ResourceManager::GetInstance();


	// Render objects in all scenes
	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	for (auto scene : scenes)
	{
		for (auto gameObject : scene->GetObjects())
		{
			// Render sprites
			for (auto sprite : gameObject->GetComponents<SpriteComponent>())
			{
				// TODO: SpriteComponent should know about its texture
				sprite->DrawSprite(resManager->GetTexture("Mummy"), gameObject->GetTransform().pos);
			}
		}
	}

	// Render To Texture As all Scene is drawn
	// blah blah render texture
	// convert void pointer to pointer of the texture
	// pass to mrGui

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (glfwWindowShouldClose(_window->GetWindow()))
	{
		// Queue engine shutdown
		_engine->Shutdown();
	}

	glfwSwapBuffers(_window->GetWindow());
}

void Hudson::Render::Renderer::WaitForRender()
{
	// TODO: FPS limiter goes here
}

GLFWwindow* Hudson::Render::Renderer::GetWindow()
{
	return _window->GetWindow();
}
