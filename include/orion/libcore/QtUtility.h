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

#ifndef ORION_LIBCORE_QTUTILITY_H
#define ORION_LIBCORE_QTUTILITY_H

namespace orion
{
	namespace libcore
	{
		// This class contains some useful functions wrapped around Qt.
		class QtUtility
		{
		public:
			// Returns the character matching the specified Qt Key code.
			static char GetCharForKey(int qt_key);
		};
	}
}

#endif