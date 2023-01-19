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
                sprite->DrawSprite(resManager->GetTexture("Mummy"), glm::vec2(200.0f, 200.0f));
            }
        }
    }

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
