/*
 * CheckMaps.cpp
 *
 *  Created on: Feb 10, 2011
 *      Author: Marco.Maneta
 */

#include "Basin.h"

void Basin::CheckMaps(Control &ctrl) {

	UINT4 r, c;

	for (unsigned int j = 0; j < _vSortedGrid.cells.size(); j++) {
		r = _vSortedGrid.cells[j].row;
		c = _vSortedGrid.cells[j].col;
		try {

			if (_vSortedGrid.cells[j].dir < 1
					|| _vSortedGrid.cells[j].dir > 9) {
				string e("The drain direction map is not a valid ldd map...\n");
				throw e;
			}

			if (_slope->matrix[r][c] == _slope->nodata) {
				string e(
						"Slope map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_slope->matrix[r][c] == 0)
				_slope->matrix[r][c] = MIN_SLOPE;
			if (_slope->matrix[r][c] <= 0) {
				string e(
						"Slope map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_Ksat->matrix[r][c] == _Ksat->nodata) {
				string e(
						"Ksat map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_slope->matrix[r][c] <= 0) {
				string e(
						"Slope map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_porosity->matrix[r][c] == _porosity->nodata) {
				string e(
						"Porosity map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_porosity->matrix[r][c] <= 0) {
				string e(
						"Porosity map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_psi_ae->matrix[r][c] == _psi_ae->nodata) {
				string e(
						"Air entry pressure map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_psi_ae->matrix[r][c] <= 0) {
				string e(
						"Air entry pressure map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_BClambda->matrix[r][c] == _BClambda->nodata) {
				string e(
						"Brooks and Cory lambda map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_BClambda->matrix[r][c] <= 0.01) {
				string e(
						"WARNING: Brooks and Corey lambda map is too small, switching to minimum value of 0.01...\n");
				cout << e;
				_BClambda->matrix[r][c] = 0.01;
				//throw e;
			}

			if (_theta_r->matrix[r][c] == _theta_r->nodata) {
				string e(
						"residual moisture map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_theta_r->matrix[r][c] <= 0) {
				string e(
						"residual moisture map contains negative or zero values inside the valid domain...\n");
				throw e;
			}
			if (_theta_r->matrix[r][c] > _porosity->matrix[r][c]) {
				string e(
						"Residual soil moisture map is larger porosity than inside the valid domain...\n");
				throw e;
			}

			if (_soildepth->matrix[r][c] == _soildepth->nodata) {
				string e(
						"soil depth map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_soildepth->matrix[r][c] < 0) {
				string e(
						"soil depth map contains negative values inside the valid domain...\n");
				throw e;
			}

			if (_paramWc->matrix[r][c] == _paramWc->nodata) {
				string e(
						"Soil parameter Wc map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_paramWc->matrix[r][c] <= 0) {
				string e(
						"Soil parameter Wc map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_paramWp->matrix[r][c] == _paramWp->nodata) {
				string e(
						"Soil parameter Wp map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_paramWp->matrix[r][c] <= 0) {
				string e(
						"Soil parameter Wp map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_meltCoeff->matrix[r][c] == _meltCoeff->nodata) {
				string e(
						"Snowmelt coefficient map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_meltCoeff->matrix[r][c] <= 0) {
				string e(
						"Snowmelt coefficient map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_snow->matrix[r][c] == _snow->nodata) {
				string e(
						"Initial SWE map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_snow->matrix[r][c] < 0) {
				string e(
						"Initial SWE map contains negative values inside the valid domain...\n");
				throw e;
			}

			if (_albedo->matrix[r][c] == _albedo->nodata) {
				string e(
						"Albedo map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_albedo->matrix[r][c] <= 0) {
				string e(
						"Albedo map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_emiss_surf->matrix[r][c] == _emiss_surf->nodata) {
				string e(
						"Surface emissivity map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_emiss_surf->matrix[r][c] <= 0) {
				string e(
						"Surface emissivity map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_soil_dry_heatcap->matrix[r][c] == _soil_dry_heatcap->nodata) {
				string e(
						"Soil dry heat capacity map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_soil_dry_heatcap->matrix[r][c] <= 0) {
				string e(
						"Soil dry heat capacity map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_soil_dry_thermcond->matrix[r][c]
					== _soil_dry_thermcond->nodata) {
				string e(
						"Dry soil thermal conductivity map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_soil_dry_thermcond->matrix[r][c] <= 0) {
				string e(
						"Dry soil thermal conductivity map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_dampdepth->matrix[r][c] == _dampdepth->nodata) {
				string e(
						"Thermal soil damping depth map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_dampdepth->matrix[r][c] <= 0) {
				string e(
						"Thermal soil damping depth map contains negative or zero values inside the valid domain...\n");
				throw e;
			}

			if (_Temp_d->matrix[r][c] == _Temp_d->nodata) {
				string e(
						"Soil temp at damp depth map contains no data values inside the valid domain...\n");
				throw e;
			}

			if (_soilmoist->matrix[r][c] == _soilmoist->nodata) {
				string e(
						"Initial soil moisture map contains no data values inside the valid domain...\n");
				throw e;
			}
			if (_soilmoist->matrix[r][c] <= 0) {
				string e(
						"Topsoil Initial soil moisture map contains negative or zero values inside the valid domain...\n");
				throw e;
			}
			if (_soilmoist->matrix[r][c] < _theta_r->matrix[r][c]) {
				string e(
						"Topsoil Initial soil moisture map is lower than residual moisture inside the valid domain...\n");
				throw e;
			}
			if (_soilmoist->matrix[r][c] > _porosity->matrix[r][c]) {
				string e(
						"Topsoil Initial soil moisture map is larger than porosity inside the valid domain...\n");
				throw e;
			}
			if (_channelmask->matrix[r][c] != 1
					&& _channelmask->matrix[r][c] != 0) {
				string e(
						"The channel mask contains funny values that are now allowed\n");
				throw e;
			}

			if (ctrl.toggle_soil_water_profile == 2) {
				if (_soilmoist2->matrix[r][c] == _soilmoist2->nodata) {
					string e(
							"Initial soil moisture map in layer 2 contains no data values inside the valid domain...\n");
					throw e;
				}
				if (_soilmoist3->matrix[r][c] == _soilmoist3->nodata) {
					string e(
							"Initial soil moisture map in layer 3 contains no data values inside the valid domain...\n");
					throw e;
				}
				if (_soilmoist2->matrix[r][c] < _theta_r->matrix[r][c]) {
					string e(
							"Initial soil moisture map in layer 2 is lower than residual moisture inside the valid domain...\n");
					throw e;
				}
				if (_soilmoist2->matrix[r][c] > _porosity->matrix[r][c]) {
					string e(
							"Initial soil moisture map in layer 2 is larger than porosity inside the valid domain...\n");
					throw e;
				}
				if (_soilmoist3->matrix[r][c] < _theta_r->matrix[r][c]) {
					string e(
							"Initial soil moisture map in layer 3 is lower than residual moisture inside the valid domain...\n");
					throw e;
				}
				if (_soilmoist3->matrix[r][c] > _porosity->matrix[r][c]) {
					string e(
							"Initial soil moisture map in layer 3 is larger than porosity inside the valid domain...\n");
					throw e;
				}

			}

		} catch (string &e) {
			cout << e;
			cout << "In row " << r << " col " << c << endl;
			throw;
		}

	}
}
