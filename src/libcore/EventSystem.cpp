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

#include <orion/libcore/EventSystem.h>

namespace orion
{
	namespace libcore
	{
		std::unordered_map<std::string, std::vector<EventSystem::EventHandler*>> EventSystem::s_handlers;
		boost::mutex EventSystem::s_mutex;

		void EventSystem::RegisterEventHandler(std::string event_id, EventHandler* handler)
		{
			if (s_handlers.count(event_id) == 0)
			{
				s_handlers.insert(std::make_pair(event_id, std::vector<EventHandler*>()));
			}

			std::vector<EventHandler*>& handlers = s_handlers.at(event_id);

			s_mutex.lock();

			handlers.push_back(handler);

			s_mutex.unlock();
		}

		void EventSystem::UnregisterEventHandler(std::string event_id, EventHandler* handler)
		{
			std::vector<EventHandler*>& handlers = s_handlers.at(event_id);

			s_mutex.lock();

			handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());

			s_mutex.unlock();
		}
	}
}