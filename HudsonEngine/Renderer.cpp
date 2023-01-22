#include "Renderer.h"
#include "Window.h"
#include "Common/Engine.h"
#include "Common/ResourceManager.h"
#include "Entity/GameObject.h"
#include "Render/SpriteComponent.h"
#include "World/Scene.h"

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

	InitRenderToTexture(1280, 720);

	// TODO Have the resource manager load shaders and textures in dynamically - Brandon B
	// I may make it so that when creating components we pass in the resource manager so the constructor adds things to it
	// Resource manager is per scene so this needs to be taken into account might be best for the devs to control which resource manager holds data when creating scenes
	// Bit of explicitness never harmed anyone

	// VERY VERY TEMPORARY, DO NOT KEEP THIS HERE

	// TODO move this into Demo Project as all loading should be handled by the creation of a scene
	auto resManager = Hudson::Common::ResourceManager::GetInstance();

	resManager->LoadShader("shaders/SpriteVertShader.glsl", "shaders/SpriteFragShader.glsl", std::string("spriteShader"));

	resManager->GetShader("spriteShader")->Use().SetInteger("image", 0);
	resManager->GetShader("spriteShader")->SetMatrix4("projection", _defaultCamera.GetProjectionMatrix());
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

	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void Hudson::Render::Renderer::InitRenderToTexture(int screenWidth, int screenHeight)
{

	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->screenVertexArrayObject);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->screenVertexArrayObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	auto resManager = Hudson::Common::ResourceManager::GetInstance();
	screenShader = resManager->LoadShader("Render/shaders/renderTextureVert.glsl", "Render/shaders/renderTextureFrag.glsl", std::string("screenShader"));

	// TODO this may need slight rework depending on window resizing as the framebuffers are tied to screen size, so a callback into initializing the frame buffers might be needed

	glGenFramebuffers(1, &frameBufferObject);
	// All the next read and write framebuffer operations will affect the currently bound framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);

	// Create texture color buffer
	glGenTextures(1, &textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // May need GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

	// Possible need for depth testing
	// TODO Test if depth management is required

	//unsigned int renderBufferObject;
	//glGenRenderbuffers(1, &renderBufferObject);
	//glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


void Hudson::Render::Renderer::Draw()
{

	// TODO replace with per-scene
	auto resManager = Hudson::Common::ResourceManager::GetInstance();

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	// Clear back buffer
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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
				sprite->DrawSprite(gameObject->GetTransform().pos);
			}
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader->Use();
	glBindVertexArray(screenVertexArrayObject);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);

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
