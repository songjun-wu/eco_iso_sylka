/*
 * sativa.h
 *
 *  Created on: Jul 30, 2010
 *      Author: Marco.Maneta
 */

#ifndef SATIVA_H_
#define SATIVA_H_

#define VERSION "V 5.1.2beta2"

#include "Basin.h"
#include "Atmosphere.h"
#include "Budget.h"
#include "Report.h"



extern Basin *oBasin;
extern Atmosphere *oAtmosphere;
extern Control *oControl;
extern Budget *oBudget;
extern Report *oReport;

extern ofstream ofSummary;

void Splash(int argc, char* argv[]);
int CreateWorld(char* argv[]);
int SolveTimeStep();
int CalculateBudgets();
int Report2Screen();
int Report2Maps();
int CrunchWorld();

void GenerateConfigTemplate(const char *fn);
#endif /* SATIVA_H_ */
