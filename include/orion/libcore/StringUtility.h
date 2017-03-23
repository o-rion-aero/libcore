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

#ifndef ORION_LIBCORE_STRINGUTILITY_H
#define ORION_LIBCORE_STRINGUTILITY_H

#include <vector>
#include <string>

namespace orion
{
	namespace libcore
	{
		// This class contains useful functions for string manipulation.
		class StringUtility
		{
		public:
			// Explodes the specified string into a vector of strings using the specified delimiter.
			static std::vector<std::string>		explode(std::string const & s, char delim);
			// Parses a Degrees-Minutes-Second string in IVAO custom format.
			static double						parse_dms2(std::string const& dms2);
		};
	}
}

#endif