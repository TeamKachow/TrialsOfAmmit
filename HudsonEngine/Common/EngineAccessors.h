#pragma once

namespace Hudson
{
    namespace World
    {
        class SceneManager;
    }
    namespace Physics
    {
        class PhysicsManager;
    }
    namespace Render
    {
        class Renderer;
    }
    namespace Input
    {
        class InputManager;
    }
}

namespace Hudson::Common
{
    class Engine;

    class EngineAccessors
    {
    protected:
        virtual Hudson::Common::EngineAccessors* GetEngineAccessorDelegate() = 0;

    public:
        virtual Input::InputManager* GetInputManager();
        //Audio::AudioManager* GetAudioManager();
        virtual Hudson::Render::Renderer* GetRenderer();
        virtual Hudson::Physics::PhysicsManager* GetPhysicsManager();
        virtual Hudson::World::SceneManager* GetSceneManager();
        virtual Hudson::Common::Engine* GetEngine();
    };
}
