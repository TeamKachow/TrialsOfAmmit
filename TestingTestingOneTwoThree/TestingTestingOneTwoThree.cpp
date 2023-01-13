#include <iomanip>
#include <iostream>
#include <vector>

#include "HudsonEngine/Entity/Component.h"
#include "HudsonEngine/Entity/GameObject.h"

using namespace Hudson::Entity;

class HelloComponent : public Component
{
};

class WorldComponent : public Component
{
};

class NotAComponent {};

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
    auto mcqueen = new GameObject();
    auto mater = new GameObject();

    // add some custom components
    auto comp1 = mcqueen->AddComponent(new HelloComponent());
    auto comp2 = mcqueen->AddComponent(new HelloComponent());

    // try adding a component twice
    auto comp3 = mcqueen->AddComponent(new WorldComponent());
    mcqueen->AddComponent(comp3);

    // search for specific component and log
    logComponentPtrs(mcqueen->GetComponents<HelloComponent>());

    // this class isn't a component - fails the is_component concept
    //lightning->GetComponents<NotAComponent>();

    // try adding a component to both
    auto comp4 = mater->AddComponent(new WorldComponent());
    mcqueen->AddComponent(comp4);
    
    std::cout << "\n";
    // search for all components and log
    logComponentPtrs(mcqueen->GetComponents<Component>());
    std::cout << "\n";

    // remove one of the object's components
    mcqueen->RemoveComponent(comp1);
    
    logComponentPtrs(mcqueen->GetComponents<Component>());
    std::cout << "\n";

    delete mcqueen;
    return 0;
}
