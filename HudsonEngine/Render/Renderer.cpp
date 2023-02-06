#include "../Render/Renderer.h"

#include "../Hudson.h"
#include "../Render/Window.h"
#include "../Common/Engine.h"
#include "../Common/ResourceManager.h"
#include "../Entity/GameObject.h"
#include "../World/Scene.h"

//
//void framebufferSizeCallback(GLFWwindow* window, int width, int height)
//{
//	Hudson::Render::Renderer::CreateFramebuffers(width, height);
//	glViewport(0, 0, width, height);
//}

void Hudson::Render::Renderer::UpdateSetShaders()
{
	auto resManager = Hudson::Common::ResourceManager::GetInstance();
	if (!screenShader)
	{
		screenShader = resManager->GetShader("screenShader");
	}
}

Hudson::Render::Renderer::Renderer(Common::Engine* engine) :
	_engine(engine),
	_window(std::make_unique<Window>(1280, 720, "DemoGame (TEMP): Hudson render window")),
    _imguiDockspace(false)
{
	static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;

#ifdef _DEBUG
	io.IniFilename = "editor.ini";
#endif

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window->GetWindow(), false);
	ImGui_ImplOpenGL3_Init("#version 460");

	// Depth is enabled by default but needs to be disabled for RTT to work
	// Due to it being 2D rendering we can disable this from the start

	glGenFramebuffers(1, &frameBufferObject);
	glGenTextures(1, &textureColorBuffer);
	glGenRenderbuffers(1, &depthBuffer);

	InitRenderToTexture();

	// Bind callback for glfw
	//glfwSetFramebufferSizeCallback(_window->GetWindow(), CreateFramebuffers);

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

	if (_imguiDockspace)
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}

}

void Hudson::Render::Renderer::InitRenderToTexture()
{
	unsigned int VBO;
	float vertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &this->screenVertexArrayObject);
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->screenVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(this->screenVertexArrayObject);

	CreateFramebuffers(_window.get()->GetWindowExtent().x, _window.get()->GetWindowExtent().y);

}

void Hudson::Render::Renderer::CreateFramebuffers(unsigned int extentWidth, unsigned int extentHeight)
{
	// All the next read and write framebuffer operations will affect the currently bound framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);

	// Create texture color buffer
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, extentWidth, extentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // May need GL_LINEAR 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, extentWidth, extentHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, extentWidth, extentHeight);

}


void Hudson::Render::Renderer::Draw()
{
	// TODO replace with per-scene
	//auto resManager = Hudson::Common::ResourceManager::GetInstance();
	UpdateSetShaders();

	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glEnable(GL_DEPTH_TEST);
	// Clear back buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);

	// Render objects in all scenes
	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	for (auto scene : scenes)
	{
		// Don't render scenes if the render flag is disabled
		if (!scene->IsRendering())
			continue;

		for (auto gameObject : scene->GetObjects())
		{
			// Render sprites
			for (auto sprite : gameObject->GetComponents<SpriteComponent>())
			{
				Shader* shader = sprite->GetShader();
				if (shader && _camera)
				{
					shader->Use().SetMatrix4("projection", _camera->GetProjectionMatrix());
					sprite->DrawSprite(gameObject->GetTransform().pos);
				}
			}

			for (auto text : gameObject->GetComponents<TextComponent>())
			{
				Shader* shader = text->GetShader();
				if (shader && _camera)
				{
					shader->Use().SetMatrix4("projection", _camera->GetProjectionMatrix());
					text->Draw(gameObject->GetTransform().pos);
				}
			}
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
	//nowTime = glfwGetTime();
	//deltaTime = nowTime - lastTime;
	//lastTime = nowTime;


	//// TODO: FPS limiter goes here

	//std::cout << "Render Delta: " << deltaTime << std::endl;
	//deltaTime = 0;

}

void Hudson::Render::Renderer::SetImguiDockspace(bool enabled)
{
	_imguiDockspace = enabled;
}

