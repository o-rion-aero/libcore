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

#include <orion/libcore/FileUtility.h>

#include <boost/filesystem.hpp>

#if WIN32
#include <ShlObj.h>
#endif

namespace orion
{
	namespace libcore
	{
		std::string FileUtility::GetOrionRCPath(const char* sub_path)
		{
			std::string path;

#if WIN32
			char winPath[1024];
			SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, winPath);
			path.append(winPath);
			path.append("\\.orion\\");
#else
			path.append("~/.orion/");
#endif

			path.append(sub_path);

			if (!boost::filesystem::exists(path))
				boost::filesystem::create_directories(path);

			return path;
		}
	}
}