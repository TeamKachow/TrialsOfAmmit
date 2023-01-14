#pragma once

namespace Hudson::World
{
    // forward declare
    class SceneManager;
    class Scene;
 
    /**
     * \brief The type of scene.
     */
    enum class SceneType
    {
        /**
         * \brief An engine scene. These are used for debugging the game/editor.
         */
        ENGINE = 0x00,
        /**
         * \brief A game scene. This is part of the running game.
         */
        GAME = 0x10,
        /**
         * \brief An editor scene. These make up the editor interface and functionality. 
         */
        EDITOR = 0x20,
        /**
         * \brief A game scene within the editor's "edit" mode.
         */
        EDITOR_GAME_EDIT = 0x21,
        /**
         * \brief A game scene within the editor's "run" mode.
         */
        EDITOR_GAME_RUN = 0x22,
    };
}
