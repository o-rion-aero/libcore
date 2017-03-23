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

#include <orion/libcore/QtUtility.h>

#include <QWidget>

namespace orion
{
	namespace libcore
	{
		char QtUtility::GetCharForKey(int qt_key)
		{
			switch (qt_key)
			{
				case Qt::Key_A: return 'A';
				case Qt::Key_B: return 'B';
				case Qt::Key_C: return 'C';
				case Qt::Key_D: return 'D';
				case Qt::Key_E: return 'E';
				case Qt::Key_F: return 'F';
				case Qt::Key_G: return 'G';
				case Qt::Key_H: return 'H';
				case Qt::Key_I: return 'I';
				case Qt::Key_J: return 'J';
				case Qt::Key_K: return 'K';
				case Qt::Key_L: return 'L';
				case Qt::Key_M: return 'M';
				case Qt::Key_N: return 'N';
				case Qt::Key_O: return 'O';
				case Qt::Key_P: return 'P';
				case Qt::Key_Q: return 'Q';
				case Qt::Key_R: return 'R';
				case Qt::Key_S: return 'S';
				case Qt::Key_T: return 'T';
				case Qt::Key_U: return 'U';
				case Qt::Key_V: return 'V';
				case Qt::Key_W: return 'W';
				case Qt::Key_X: return 'X';
				case Qt::Key_Y: return 'Y';
				case Qt::Key_Z: return 'Z';
				case Qt::Key_Space: return ' ';
				case Qt::Key_0: return '0';
				case Qt::Key_1: return '1';
				case Qt::Key_2: return '2';
				case Qt::Key_3: return '3';
				case Qt::Key_4: return '4';
				case Qt::Key_5: return '5';
				case Qt::Key_6: return '6';
				case Qt::Key_7: return '7';
				case Qt::Key_8: return '8';
				case Qt::Key_9: return '9';
				case Qt::Key_Plus: return '+';
				case Qt::Key_Minus: return '-';
				default: return 0x00;
			}
		}
	}
}