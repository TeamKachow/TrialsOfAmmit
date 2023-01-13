#pragma once
#include <concepts>

namespace Hudson::Entity
{
    class Component;
    class GameObject;
    class Behaviour;

    /**
     * Concepts let you limit what types can be passed in as template parameters.
     * This tells the compiler to enforce certain properties on classes you pass in to template functions.
     */

    // Ensures that a type extends from Component
    template<typename T>
    concept is_component = std::is_base_of_v<Component, T>;

    // Ensures that a type extends from Behaviour 
    template<typename T>
    concept is_behaviour = std::is_base_of_v<Behaviour, T>;

    // Ensures that a type is an editor component; these must have a no-arg constructor and a copy constructor.
    template<typename T>
    concept is_editor_component = is_component<T> && std::is_constructible_v<T> && std::is_copy_constructible_v<T>;
    
}