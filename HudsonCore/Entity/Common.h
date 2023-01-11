#pragma once

namespace Hudson::Entity
{
    class Component;
    class GameObject;
    class Behaviour;

    /**
     * Concepts let you limit what types can be passed in as template parameters.
     * This concept ensures that a type is a component.
     */
    template<typename T>
    concept is_component = std::is_base_of_v<Component, T>;
}