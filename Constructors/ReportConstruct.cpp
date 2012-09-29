/*
 * ReportConstruct.cpp
 *
 *  Created on: Sep 21, 2010
 *      Author: Marco.Maneta
 */

#include"Grid.h"
#include"Report.h"


Report::Report(Control &ctrl){

	grid *temp;

	temp = new grid(ctrl.path_BasinFolder + ctrl.fn_rep_mask, ctrl.MapType);

	 UINT4 r, c, data = 0;
	 r = temp->r;
	 c = temp->c;

	 for (UINT4 i=0; i<r; i++)
	    {
	        for (UINT4 j=0; j<c; j++)
	        {
	           data = (UINT4)temp->matrix[i][j];
	        	if( data <= 0 || data >= 32) continue;
	           mask.cells.push_back(cell(i,j,(int)data));
	        }
	    }


	if(temp)
		delete temp;

}
