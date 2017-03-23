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

#include <orion/libcore/StringUtility.h>
#include <sstream>

namespace orion
{
	namespace libcore
	{
		std::vector<std::string> StringUtility::explode(std::string const & s, char delim)
		{
			std::vector<std::string> result;
			std::istringstream iss(s);

			for (std::string token; std::getline(iss, token, delim);)
			{
				result.push_back(std::move(token));
			}

			return result;
		}

		double StringUtility::parse_dms2(std::string const& dms2)
		{
			bool neg;
			int dddmax = 0;
			int ddd = 0;
			int mm = 0;
			double ss = 0;

			// check first character for east/west/north/south indicator
			switch (dms2.at(0))
			{
			case 'W':
			case 'w':
				dddmax = 180;
				neg = true;
				break;
			case 'E':
			case 'e':
				dddmax = 180;
				neg = false;
				break;
			case 'N':
			case 'n':
				dddmax = 90;
				neg = false;
				break;
			case 'S':
			case 's':
				dddmax = 90;
				neg = true;
				break;
			default:
				// incorrect value returns 0
				return 0;
			}

			// convert to integer & float
			ddd = atoi(dms2.substr(1, 3).c_str());
			mm = atoi(dms2.substr(4, 2).c_str());
			ss = atof((dms2.substr(6, 2) + "." + dms2.substr(8, std::string::npos)).c_str());

			// return final result
			if (neg)
				return -(ddd + (mm / 60.0) + (ss / 3600.0));
			return (ddd + (mm / 60.0) + (ss / 3600.0));
		}
	}
}