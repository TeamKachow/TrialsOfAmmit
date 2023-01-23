#include "Engine.h"

#include "../Entity/GameObject.h"
#include "../Renderer.h"

Hudson::Common::Engine::Engine()
{
}

Hudson::Common::Engine::~Engine()
{
}

void Hudson::Common::Engine::Setup()
{
    // create scene manager
    _sceneManager = std::make_unique<Hudson::World::SceneManager>();

    // create renderer
    _renderer = std::make_unique<Render::Renderer>(this);

    // create physics
    _physics = std::make_unique<Physics::PhysicsManager>(this);

    // create audio system

    // create input system

}

void Hudson::Common::Engine::Run()
{
    bool shouldExit = false;
    while (!shouldExit)
    {
        // ImGui
        _renderer->StartImGui();

        // Tick the scene manager (runs Behaviours)
        _sceneManager->Tick();

        // TODO: _audioManager->Update();

        _physics->UpdatePhysics();

        // Call imgui hooks
        for (std::function<void(Engine*)> hook : _frameHooks)
        {
            hook(this);
        }

        ImGui::ShowDemoWindow();

        // Render scene
        _renderer->WaitForRender();
        _renderer->Draw();

        // Poll GLFW events
        glfwPollEvents();

        // Exit if either glfw wants to shut down or Engine::Shutdown was called somewhere
        shouldExit = _shutdownFlag;
    }

}

void Hudson::Common::Engine::Shutdown()
{
    _shutdownFlag = true;
}

void Hudson::Common::Engine::Cleanup()
{

}

Hudson::World::SceneManager* Hudson::Common::Engine::GetSceneManager() const
{
    return _sceneManager.get();
}

void Hudson::Common::Engine::RegisterFrameHook(std::function<void(Engine*)> frameHook)
{
    _frameHooks.push_back(frameHook);
}
