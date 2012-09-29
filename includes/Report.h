/*
 * Report.h
 *
 *  Created on: Sep 21, 2010
 *      Author: Marco.Maneta
 */

#ifndef REPORT_H_
#define REPORT_H_

#include "SortGrid.h"
#include "InitConf.h"

//Map write defines
#define WriteMapSeries(_var, _s, _tscount)  \
     _var->grid2PCRMap( (oControl->path_ResultsFolder + ParseString(_s, _tscount)).c_str(), CR_REAL4, VS_SCALAR);

#define WriteMap(_var, _s) \
     _var->MatrixToMap((pathout + _s).c_str(), CR_REAL4, VS_SCALAR);


struct Report{

	vectCells mask;

	Report(){};
	Report(Control &ctrl);

	int ReportTimeSeries(const grid *input, string filename, float timestep);
	int ReportVectCells(const vectCells *input, string filename, float timestep);
	int RenameFile(string oldname);

};
#endif /* REPORT_H_ */
