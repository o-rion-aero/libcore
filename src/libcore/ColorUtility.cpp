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

#include <orion/libcore/ColorUtility.h>

namespace orion
{
	namespace libcore
	{
		void ColorUtility::ParseHexColor(std::string& str, float* output_4f)
		{
			output_4f[0] = strtol(str.substr(1, 2).c_str(), 0, 16) / 255.0f;
			output_4f[1] = strtol(str.substr(3, 2).c_str(), 0, 16) / 255.0f;
			output_4f[2] = strtol(str.substr(5, 2).c_str(), 0, 16) / 255.0f;
			
			if (str.length() > 7)
				output_4f[3] = strtol(str.substr(7, 2).c_str(), 0, 16) / 255.0f;
			else
				output_4f[3] = 1.0f;			
		}
	}
}