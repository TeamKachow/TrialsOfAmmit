#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Common
{
    /**
     * \brief Holds a vector of objects, to which modifications can be queued until a fixed point in time.
     * \details Additions and removals will be queued and run in order. Take care if adding/removing multiple times!
     * \tparam T The type of object to hold
     */
    template <typename T>
    class QueuingObjectHolder
    {
    private:
        enum class Action { ADD, REMOVE };
        std::vector<T> _current;
        std::vector<std::pair<T, Action>> _pending;
        std::function<void(std::pair<T, Action>&)> _callback;

    public:
        /**
         * \brief Create a queuing object holder.
         * \param callback An optional callback to run after the queued action has run
         */
        QueuingObjectHolder(std::function<void(std::pair<T, Action>&)> callback = {}) : _callback(callback)
        {}

        /**
         * \brief Get a view of the object currently held at this point in time.
         * \return A view of currently-held objects.
         */
        const std::vector<T>& Get() const
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
                case Action::ADD:
                    _current.push_back(action.first);
                    break;
                case Action::REMOVE:
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
        }

        /**
         * \brief Queue an object to be added on the next update.
         * \param object The object to queue for addition
         */
        void Add(T object)
        {
            _pending.push_back(std::make_pair(object, Action::ADD));
        }

        /**
         * \brief Queue an object to be removed on the next update.
         * \param object The object to queue for removal
         */
        void Remove(T object)
        {
            _pending.push_back(std::make_pair(object, Action::REMOVE));
        }
    };

}
