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

#ifndef ORION_LIBCORE_COLORUTILITY_H
#define ORION_LIBCORE_COLORUTILITY_H

#include <string>

namespace orion
{
	namespace libcore
	{
		// This class contains useful functions for color data manipulations
		// such as parsing from strings and converting between formats.
		class ColorUtility
		{
		public:
			// Converts the specified hexadecimal color string into a 4 channel RGBA array
			// output_4f must be an array of floats of size at least 4.
			static void	ParseHexColor(std::string& str, float* output_4f);
		};
	}
}

#endif