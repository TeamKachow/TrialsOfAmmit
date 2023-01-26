#pragma once
#include "../Util/stdafx.h"
#include "../Entity/Common.h"

namespace Hudson::Editor
{
    /**
     * \brief A registry providing runtime type information about components that are available in the game.
     */
    class ComponentRegistry
    {
    private:
        struct Entry
        {
            std::string name;
            std::function<Entity::Component* ()> constructor;

            // TODO: explore using a proper runtime type info library
            // to anyone who ever has to deal with this, I'm sorry
            // - boost::describe?
            // - boost::preprocessor?
            // - https://www.rttr.org/ ?
        };

        std::vector<Entry> _entries;

    public:
        /**
         * \brief Register a component or behaviour to be visible to the editor.
         * \tparam T The class of the component/behaviour to register
         * \param name The name of the component/behaviour to register
         */
        template<Entity::is_editor_component T>
        void Register(std::string name);

        /**
         * \brief Register engine components to be visible in the editor.
         */
        void RegisterEngineComponents();

        /**
         * \brief Get all registered components.
         * \return The registered components
         */
        std::vector<Entry>& GetKnownComponents();
    };

    template <Entity::is_editor_component T>
    void ComponentRegistry::Register(std::string name)
    {
        _entries.emplace_back(name, [] { return new T(); });
    }
}
