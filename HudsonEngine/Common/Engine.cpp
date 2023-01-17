#include "Engine.h"
#include <chrono>
#include <thread>

#include "../Entity/GameObject.h"
#include "../World/Scene.h"

// TODO: EVERYTHING

Hudson::Common::Engine::Engine(std::function<void(Engine*)> onSetupComplete)
{
}

Hudson::Common::Engine::~Engine()
{
}

void Hudson::Common::Engine::Setup()
{
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

        // Render scene
        //std::this_thread::sleep_for(100)
        // TODO(?): _renderer->SleepUntilDraw();
        // TODO: _renderer->Draw();

        // Exit if either glfw wants to shut down or Engine::Shutdown was called somewhere
        //shouldExit = _shutdownFlag || glfwShouldWindowClose();
    }

}

void Hudson::Common::Engine::Shutdown()
{
    _shutdownFlag = true;
}

void Hudson::Common::Engine::Cleanup()
{
}
