#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Common
{
    /**
     * \brief Holds a set of objects, to which modifications can be queued until a fixed point in time.
     * \details Additions and removals will be queued and run in order. Take care if adding/removing multiple times between updates!
     * \tparam T The type of object to hold
     */
    template <typename T>
    class DeferredObjectSet
    {
    public:
        enum class ActionType { ADD, REMOVE };
        using Action = std::pair<T, ActionType>;

    private:
        std::set<T> _current;
        std::vector<Action> _pending;
        std::function<void(Action&)> _callback;

    public:
        /**
         * \brief Create a queuing object holder.
         * \param callback An optional callback to run after the queued action has run
         */
        DeferredObjectSet(std::function<void(Action&)> callback = {}) : _callback(callback)
        {}

        /**
         * \brief Get a view of the object currently held at this point in time.
         * \return A view of currently-held objects.
         */
        const std::set<T>& Get() const
        {
            return _current;
        }

        /**
         * \brief Run any pending addition/removal operations.
         */
        void Update()
        {
            for (auto action : _pending)
            {
                switch (action.second)
                {
                case ActionType::ADD:
                    _current.insert(action.first);
                    break;
                case ActionType::REMOVE:
                    _current.erase(action.first);
                    break;
                default:
                    assert(false);
                    break;
                }
                if (_callback)
                {
                    _callback(action);
                }
            }

            _pending.clear();
        }

        /**
         * \brief Queue an object to be added on the next update.
         * \param object The object to queue for addition
         */
        void Add(T object)
        {
            _pending.push_back(std::make_pair(object, ActionType::ADD));
        }

        /**
         * \brief Queue an object to be removed on the next update.
         * \param object The object to queue for removal
         */
        void Remove(T object)
        {
            _pending.push_back(std::make_pair(object, ActionType::REMOVE));
        }

        /**
         * \brief Register the callback to run after individual set update. This may run multiple times per Update call.
         * \param callback A callback to run after each update of the set.
         */
        void SetCallback(std::function<void(Action&)> callback)
        {
            _callback = callback;
        }

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(DeferredObjectSet<T>, _current)
    };
}
