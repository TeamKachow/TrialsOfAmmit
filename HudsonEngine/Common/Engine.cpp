#include "Engine.h"

#include "../Entity/GameObject.h"
#include "../Renderer.h"

// TODO: EVERYTHING

Hudson::Common::Engine::Engine(std::function<void(Engine*)> onSetupComplete)
{
    _postSetup = onSetupComplete;
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

    // run post-setup hook
    _postSetup(this);
}

void Hudson::Common::Engine::Run()
{
    bool shouldExit = false;
    while (!shouldExit)
    {
        // Tick the scene manager (runs Behaviours)
        _sceneManager->Tick();

        // TODO: _audioManager->Update();
        // TODO: _physicsManager->Update();

        _physics->UpdatePhysics();

        // Render scene
        //std::this_thread::sleep_for(100)
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
