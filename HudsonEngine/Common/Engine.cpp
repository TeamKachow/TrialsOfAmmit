#include "Engine.h"

#include "../Input/InputManager.h"
#include "../Entity/GameObject.h"
#include "../Render/Renderer.h"

Hudson::Common::Engine::Engine()
{
}

Hudson::Common::Engine::~Engine()
{
}

void Hudson::Common::Engine::Setup()
{
    // create scene manager
    _sceneManager = std::make_unique<World::SceneManager>();

    // create renderer
    _renderer = std::make_unique<Render::Renderer>(this);

    // create _physics
    _physics = std::make_unique<Physics::PhysicsManager>(this);

    // create audio system
    // TODO

    // create input system
    _input = std::make_unique<InputManager>();

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

        // Call frame hooks
        for (std::function<void(Engine*)> hook : _frameHooks)
        {
            hook(this);
        }

#ifdef _DEBUG
        // Render ImGui demo window
        ImGui::ShowDemoWindow();
#endif

        // TODO Setup and ifdef or run config to tell the renderer that it can recreate it's framebuffers if GLFWwindow is resized
        // TODO when the editor is attached renderer will recreate its framebuffers based on the size of the imgui window it is rendering to

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
    // Call shutdown hooks
    for (std::function<void(Engine*)> hook : _shutdownHooks)
    {
        hook(this);
    }
}

Hudson::World::SceneManager* Hudson::Common::Engine::GetSceneManager() const
{
    return _sceneManager.get();
}

Hudson::Physics::PhysicsManager* Hudson::Common::Engine::GetPhysicsManager() const
{
    return _physics.get();
}

InputManager* Hudson::Common::Engine::GetInputManager() const
{
    return _input.get();
}

void Hudson::Common::Engine::RegisterFrameHook(std::function<void(Engine*)> frameHook)
{
    _frameHooks.push_back(frameHook);
}

void Hudson::Common::Engine::RegisterShutdownHook(std::function<void(Engine*)> shutdownHook)
{
    _shutdownHooks.push_back(shutdownHook);
}
