﻿#pragma once
#include "Common.h"
#include "Component.h"
#include "../Common/EngineAccessors.h"

// TODO: preprocessor macros that dump out metadata (?)
// references:
// - https://www.boost.org/doc/libs/1_81_0/libs/serialization/doc/serialization.html#derivedpointers
// - https://stackoverflow.com/a/1096743
// - https://unrealcpp.com/add-component/

namespace Hudson::Entity
{
    /**
     * \brief A scripted behaviour, which acts on certain parts of an object's update loop.
     */
    class Behaviour : public Component, public Common::EngineAccessors
    {
    protected:
        Hudson::Common::EngineAccessors* GetEngineAccessorDelegate() override;

    public:
        Behaviour(const char* name);

        /**
         * \brief Handles when a behaviour is added to a game object.
         */
        virtual void OnCreate() {}
        /**
         * \brief Handles when a game object's behaviours are updated.
         * \param dt The interval sicne the last update loop. (This interval should not change at runtime.)
         */
        virtual void OnTick(const double& dt) = 0;
        /**
         * \brief Handles when the behaviour is removed from its game object.
         */
        virtual void OnDestroy() {}
    };
}