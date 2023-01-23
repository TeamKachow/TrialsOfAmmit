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

        static std::vector<Entry> _entries;

    public:
        template<Entity::is_editor_component T>
        static void Register(std::string name);

        static void RegisterEngineComponents();

        // TODO: the rest of this
    };

    template <Entity::is_editor_component T>
    void ComponentRegistry::Register(std::string name)
    {
        _entries.emplace_back(name, [] { return new T(); });

        // TODO: look into boost::serialization or cereal support here?
        // TODO: ....ok we may need more advanced RTTI for this, aaaaaaaaaaaaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    }
}
