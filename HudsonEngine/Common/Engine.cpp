#include "../Common/Engine.h"

#include "../Common/ComponentRegistry.h"
#include "../AudioManager.h"
#include "../Input/InputManager.h"
#include "../Entity/GameObject.h"
#include "../Render/Renderer.h"
#include "../Render/Window.h"

static Hudson::Common::Engine* INSTANCE;

Hudson::Common::Engine::Engine()
{
    assert(INSTANCE == nullptr);
    INSTANCE = this;
}

Hudson::Common::Engine::~Engine()
{
    INSTANCE = nullptr;
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
    _audio = std::make_unique<Audio::AudioManager>();

    // create input system
    _input = std::make_unique<Hudson::Input::InputManager>();
    _input.get()->Setup(_renderer.get());

    // create component registry
    _componentRegistry = std::make_unique<Hudson::Common::ComponentRegistry>();
}

void Hudson::Common::Engine::Run()
{

    bool shouldExit = false;
    while (!shouldExit)
    {
        // Call pre-frame hooks
        for (std::function<void(Engine*)> hook : _preFrameHooks)
        {
            hook(this);
        }

        // ImGui
        _renderer->StartImGui();

        // Tick the scene manager (runs Behaviours)
        _sceneManager->Tick();

        // TODO: _audioManager->Update();

        _physics->UpdatePhysics();

        // Call mid-frame hooks
        for (std::function<void(Engine*)> hook : _midFrameHooks)
        {
            hook(this);
        }

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

Hudson::Render::Renderer* Hudson::Common::Engine::GetRenderer()
{
    return _renderer.get();
}

Hudson::World::SceneManager* Hudson::Common::Engine::GetSceneManager()
{
    return _sceneManager.get();
}

Hudson::Physics::PhysicsManager* Hudson::Common::Engine::GetPhysicsManager()
{
    return _physics.get();
}

Hudson::Audio::AudioManager* Hudson::Common::Engine::GetAudioManager()
{
    return _audio.get();
}

Hudson::Input::InputManager* Hudson::Common::Engine::GetInputManager()
{
    return _input.get();
}

Hudson::Common::Engine* Hudson::Common::Engine::GetEngine()
{
    return this;
}

Hudson::Common::ComponentRegistry* Hudson::Common::Engine::GetComponentRegistry()
{
    return _componentRegistry.get();
}

Hudson::Common::Engine* Hudson::Common::Engine::GetInstance()
{
    return INSTANCE;
}

Hudson::Common::EngineAccessors* Hudson::Common::Engine::GetEngineAccessorDelegate()
{
    return nullptr;
}

void Hudson::Common::Engine::RegisterPreFrameHook(std::function<void(Engine*)> hook)
{
    _preFrameHooks.push_back(hook);
}

void Hudson::Common::Engine::RegisterMidFrameHook(std::function<void(Engine*)> hook)
{
    _midFrameHooks.push_back(hook);
}

void Hudson::Common::Engine::RegisterShutdownHook(std::function<void(Engine*)> hook)
{
    _shutdownHooks.push_back(hook);
}

void Hudson::Common::Engine::RegisterObjectRemovalHook(std::function<void(Entity::GameObject*)> hook)
{
    _objectRemoveHooks.push_back(hook);
}

void Hudson::Common::Engine::CallObjectRemovalHooks(Entity::GameObject* removed)
{
    for (std::function<void(Entity::GameObject*)> hook : _objectRemoveHooks)
    {
        hook(removed);
    }
}
