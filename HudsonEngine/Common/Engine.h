#pragma once

#include "../World/SceneManager.h"

#include "../PhysicsManager.h"

namespace Hudson
{
    namespace Render
    {
        class Renderer;
    }
}

namespace Hudson::Common
{
    /**
     * \brief The entrypoint to the engine.
     * \details This manages the lifecycle (start -> game loop -> exit) of the game.
     */
    class Engine
    {
    private:
        std::unique_ptr<World::SceneManager> _sceneManager;
        std::unique_ptr<Render::Renderer> _renderer; 
        std::unique_ptr<Physics::PhysicsManager> _physics;
        // TODO: std::unique_ptr<AudioManager> _audio; 
        // TODO: std::unique_ptr<InputManager> _input; 

        std::function<void(Engine*)> _postSetup;
        bool _shutdownFlag = false;

    public:
        Engine(std::function<void(Engine*)> onSetupComplete);
        ~Engine();

        // TODO: figure out which things belong in which parts of the engine lifecycle
        /**
         * \brief Set up game engine resources and run setup function if provided
         */
        void Setup();

        /**
         * \brief Run the engine loop. This will return when the game/editor exits.
         */
        void Run();

        /**
         * \brief Shut down the engine at the end of the current update loop.
         * \details If currently running, this will set a flag to stop at the end of the current update loop.
         * \details This will *not* clean up the game resources - for that, see Cleanup()
         */
        void Shutdown();

        /**
         * \brief Clean up engine resources.
         */
        void Cleanup();

        [[nodiscard]] Hudson::World::SceneManager* GetSceneManager() const;
    };
}
