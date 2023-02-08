#pragma once
#include "../Util/stdafx.h"
#include "./Common.h"
#include "../Common/DeferredObjectSet.h"

namespace Hudson
{
	namespace Util
	{
		class Timestep;
	}
}

namespace Hudson::World
{
    class SceneManager
    {
    private:
        Common::DeferredObjectSet<Scene*> _scenes;

        Hudson::Util::Timestep* _time;

        bool _paused = false;
        bool _isTicking = false;

        /**
         * \brief Handles pending scene removals then additions after each tick.
         */
        void HandlePostTick();

    public:
        SceneManager();
        ~SceneManager();

        /**
         * \brief Loads a scene from a given file.
         * \param path The file to construct the scene from.
         * \return The loaded scene.
         */
        static Scene* LoadScene(const std::string& path);

        /**
         * \brief Saves a scene to a given file.
         * \param path The file to write the scene to.
         * \param scene The scene to save.
         */
        static void SaveScene(const std::string& path, Scene* scene);

        /**
         * \brief Get all the scenes currently loaded.
         * \return A set of all currently-loaded scenes.
         */
        const std::set<Scene*> GetLoadedScenes();

        /**
         * \brief Add a scene to the list of loaded scenes.
         * \warning If the scene manager is currently ticking, this will not take effect until the tick is complete!
         * \param scene The scene to add to the list of loaded scenes.
         */
        void AddScene(Scene* scene);

        /**
         * \brief Remove a scene from the list of loaded scenes.
         * \warning If the scene manager is currently ticking, this will not take effect until the tick is complete!
         * \param scene The scene to remove from the list of loaded scenes.
         */
        void RemoveScene(Scene* scene);

        /**
         * \brief Check whether the given scene is known to the scene manager.
         * \param scene The scene to check.
         */
        bool IsSceneLoaded(Scene* scene);

        /**
        * \brief Tick the current scenes.
        */
        void Tick();

        /**
         * \brief Check whether all scenes have been paused.
         * \return Whether all scenes are paused
         */
        [[nodiscard]] bool IsPaused() const;

        /**
         * \brief Set whether all scenes are paused.
         * \param paused Whether all scenes are paused
         */
        void SetPaused(bool paused);
    };
}
