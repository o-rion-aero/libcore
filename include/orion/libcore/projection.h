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

#ifndef ORION_LIBCORE_PROJECTION_H
#define ORION_LIBCORE_PROJECTION_H

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/PolarStereographic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

using namespace GeographicLib;

namespace orion
{
	namespace libcore
	{
		// An abstract projection.
		class BaseProjection
		{
		public:
			virtual void initialize(double ref_x, double ref_y, double ref_z) = 0;
			virtual void project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z) = 0;
			virtual void deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z) = 0;
		};

		// An implementation of the Lambert Conformal Projection.
		class LCCProjection : public BaseProjection
		{
		public:
			LCCProjection();
			~LCCProjection();

			void initialize(double ref_x, double ref_y, double ref_z);
			void project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z);
			void deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z);
		private:

		};

		// An implementation of the Polar Stereographic Projection.
		class PolarStereographicProjection : public BaseProjection
		{
		public:
			PolarStereographicProjection();
			~PolarStereographicProjection();

			void initialize(double ref_x, double ref_y, double ref_z);
			void project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z);
			void deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z);
		private:
		};

		// An implementation of the Cartesian Projection
		class CartesianProjection : public BaseProjection
		{
		public:
			CartesianProjection();
			~CartesianProjection();

			void initialize(double ref_x, double ref_y, double ref_z);
			void project(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z);
			void deproject(double in_x, double in_y, double in_z, double* out_x, double* out_y, double* out_z);
		private:
			LocalCartesian*	m_projection;
		};
	}
}

#endif