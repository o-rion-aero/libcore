/*
* Copyright 2017 Christophe Delondre.
*
* This file is part of ORION.
*
* ORION is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* ORION is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with ORION.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef ORION_LIBCORE_EVENTSYSTEM_H
#define ORION_LIBCORE_EVENTSYSTEM_H

#include <unordered_map>
#include <string>
#include <functional>

#include <boost/thread/mutex.hpp>

namespace orion
{
	namespace libcore
	{
		// The EventSystem allows heterogenous software components to communicate
		// within the same process through a delegate callback system.
		class EventSystem
		{
		public:
			// A standard parameter-less event handler delegate.
			typedef std::function<void()> EventHandler;

			// Register the specified handler as callback to the specified event_id.
			static void RegisterEventHandler(std::string event_id, EventHandler* handler);
			// Deletes the specified handler attached to the specified event_id.
			static void UnregisterEventHandler(std::string event_id, EventHandler* handler);

			// Raise the specified event, without parameters.
			static void RaiseEvent(std::string event_id)
			{
				if (s_handlers.count(event_id) > 0)
				{
					std::vector<EventHandler*>& handlers = s_handlers.at(event_id);

					if (handlers.size() > 0)
					{
						s_mutex.lock();

						for (unsigned int i = 0; i < handlers.size(); i++)
						{
							EventHandler* eh = handlers.at(i);

							(*eh)();
						}

						s_mutex.unlock();
					}
				}
			}

			/*template<typename... _args>
			static void raise_event(std::string event_id, _args&&... args)
			{
				if (s_handlers.count(event_id) > 0)
				{
					std::vector<void*>& handlers = s_handlers.at(event_id);

					if (handlers.size() > 0)
					{
						s_mutex.lock();

						for (unsigned int i = 0; i < handlers.size(); i++)
						{
							std::invoke(handlers.at(i), std::forward<_args>(args)...);
						}

						s_mutex.unlock();
					}
				}
			}*/
		private:
			static std::unordered_map<std::string, std::vector<EventHandler*>> s_handlers;
			static boost::mutex s_mutex;
		};
	}
}

#endif