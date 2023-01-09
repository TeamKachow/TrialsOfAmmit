#include <iomanip>
#include <iostream>

#include "HudsonCore/Entity/Component.h"
#include "HudsonCore/Entity/GameObject.h"

using namespace Hudson::Core::Entity;

class HelloComponent : public Component
{
};

class WorldComponent : public Component
{
};

template<is_component T>
void logComponentPtrs(const std::vector<T*>& components)
{
    for (auto toLog : components)
    {
        std::cout << "component: " << std::setw(16) << std::setbase(16) << toLog << "\n";
    }
}

int main(int argc, char* argv[])
{
    auto lightning = new GameObject();

    // add some custom components
    auto comp1 = lightning->AddComponent(new HelloComponent());
    auto comp2 = lightning->AddComponent(new HelloComponent());
    auto comp3 = lightning->AddComponent(new WorldComponent());

    // search for specific component and log
    logComponentPtrs(lightning->GetComponents<HelloComponent>());
    std::cout << "\n";
    // search for all components and log
    logComponentPtrs(lightning->GetComponents<Component>());
    std::cout << "\n";

    lightning->RemoveComponent(comp1);
    
    logComponentPtrs(lightning->GetComponents<Component>());
    std::cout << "\n";

    delete lightning;
    return 0;
}
