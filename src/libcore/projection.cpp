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

#include <orion/libcore/Projection.h>

/*
 *	Lambert Conformal Conic
 */

namespace orion
{
	namespace libcore
	{
		LCCProjection::LCCProjection()
		{

		}

		LCCProjection::~LCCProjection()
		{

		}

		void LCCProjection::initialize(double ref_x, double ref_y, double ref_z)
		{

		}

		void LCCProjection::project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z)
		{

		}

		void LCCProjection::deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z)
		{

		}

		/*
		*	Polar Stereographic
		*/
		PolarStereographicProjection::PolarStereographicProjection()
		{

		}

		PolarStereographicProjection::~PolarStereographicProjection()
		{

		}

		void PolarStereographicProjection::initialize(double ref_x, double ref_y, double ref_z)
		{

		}

		void PolarStereographicProjection::project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z)
		{

		}

		void PolarStereographicProjection::deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z)
		{

		}

		/*
		*	Cartesian
		*/
		CartesianProjection::CartesianProjection()
		{

		}

		CartesianProjection::~CartesianProjection()
		{
			if (m_projection)
				delete m_projection;
		}

		void CartesianProjection::initialize(double ref_x, double ref_y, double ref_z)
		{
			m_projection = new LocalCartesian(ref_x, ref_y, ref_z, Geocentric(Constants::WGS84_a(), Constants::WGS84_f()));
		}

		void CartesianProjection::project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z)
		{
			double x, y, z = 0;

			m_projection->Forward(in_x, in_y, in_z, x, y, z);

			*out_x = x;
			*out_y = y;
			*out_z = z;
		}

		void CartesianProjection::deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z)
		{
			double lat, lon, h;

			m_projection->Reverse(in_x, in_y, in_z, lat, lon, h);

			*out_x = lat;
			*out_y = lon;
			*out_z = h;
		}
	}
}