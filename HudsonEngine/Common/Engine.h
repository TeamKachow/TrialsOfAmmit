#pragma once

#include "../World/SceneManager.h"
#include "../Input/InputManager.h"
#include "../Physics/PhysicsManager.h"

class InputManager;

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
        std::unique_ptr<Input::InputManager> _input;

        bool _shutdownFlag = false;

        std::vector<std::function<void(Engine*)>> _preFrameHooks;
        std::vector<std::function<void(Engine*)>> _midFrameHooks;
        std::vector<std::function<void(Engine*)>> _shutdownHooks;

    public:
        Engine();
        ~Engine();
        
        /**
         * \brief Set up game engine resources and run setup function if provided
         */
        void Setup();

        /**
         * \brief Run the engine loop. This will return when the game/editor exits.
         */
        void Run();

        /**
		 * \brief Run the engine loop. This will return when the game/editor exits.
		 */
    	 Render::Renderer* GetRenderer() { return _renderer.get(); }

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

        /**
         * \brief Get the engine's scene manager.
         * \return The scene manager
         */
        [[nodiscard]] Hudson::World::SceneManager* GetSceneManager() const;

        /**
         * \brief Get the engine's physics manager.
         * \return The physics manager
         */
        [[nodiscard]] Physics::PhysicsManager* GetPhysicsManager() const;

        /**
         * \brief Get the engine's audio manager.
         * \return The audio manager
         */
        // TODO: Audio::AudioManager* GetAudioManager() const;

        /**
         * \brief Get the engine's input manager.
         * \return The input manager
         */
        [[nodiscard]] Input::InputManager* GetInputManager() { return _input.get(); }

        /**
         * \brief Register a hook to run before engine systems have run.
         * \param hook The function to call before engine systems run.
         */
        void RegisterPreFrameHook(std::function<void(Engine*)> hook);

        /**
         * \brief Register a hook to run after engine systems have run for the frame but before it renders.
         * \param hook The function to call before a frame renders.
         */
        void RegisterMidFrameHook(std::function<void(Engine*)> hook);

        /**
         * \brief Register a hook to run before the engine shuts down.
         * \param hook The function to call before the engine shuts down
         */
        void RegisterShutdownHook(std::function<void(Engine*)> hook);
    };
}
