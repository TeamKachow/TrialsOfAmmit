#pragma once
#include "../Util/stdafx.h"
#include "../Util/Debug.h"
#include "../Entity/Common.h"
#include "../Entity/Component.h"

namespace Hudson::Common
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
        };

        std::map<std::string, Entry> _entries;

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
        std::map<std::string, Entry>& GetKnownComponents();

        bool IsComponentRegistered(std::string& name);
    };

    template <Entity::is_editor_component T>
    void ComponentRegistry::Register(std::string name)
    {
        // check if component name matches name passed in constructor
        Entity::Component* temp = new T();
        const char* typeName = temp->GetTypeName();
        if (typeName != name)
        {
            Hudson::Util::Debug::LogError("WARNING: Trying to register a type as " + name + " but it identifies itself as " + typeName);
        }

        // store info and constructor in registry
        Entry entry = { name, [] { return new T(); } };
        _entries.insert_or_assign(name, entry);
    }
}
