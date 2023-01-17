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
        std::vector<Behaviour*> behaviours;
        std::vector<Behaviour*> sprites;
        std::vector<Behaviour*> audio;


        // todo 
        _sceneManager->Tick();

        // todo audio/physics(/behaviours?)
        _audioManager->Update();
        _physicsManager->Update();

        // renderer
        //std::this_thread::sleep_for(100)

        sceneManager->GetComponents<SpriteComponent>();
        sceneManager->GetComponents<AudioComponent>();
        sceneManager->GetComponents<RigidbodyComponent>();
        sceneManager->GetComponents<CollisionComponent>();
        sceneManager->GetComponents<Behaviour>();



        for (auto scene : _sceneManager->GetLoadedScenes())
        {

            for (auto object : scene->GetObjects())
            {
                std::vector<SpriteComponent*> blah = object->GetComponents<SpriteComponent>();
            }
        }

        _renderer->Draw();
    }

}

void Hudson::Common::Engine::Shutdown()
{
}

void Hudson::Common::Engine::Cleanup()
{
}
