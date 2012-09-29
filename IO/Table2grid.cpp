/*
 * ReadASCIItable.cpp
 *
 *  Created on: Jun 17, 2010
 *      Author: marco
 */

#include <fstream>
#include "Grid.h"

int Table2Grid(std::string fname, grid *pnt){

			ifstream input;
			UINT4 rows, cols;
			REAL8 values;

			try{

			  input.open(fname.c_str());
			        if(!input.is_open()){
			         cerr << "Couldn't open file " << fname << endl;
			         exit(EXIT_FAILURE);
			        }
			  }catch(const exception& e){

			    cerr << "Couldn't open file " << fname << " with message " << e.what() << endl;
			    exit(EXIT_FAILURE);
			  }


		    input >> rows;
		    input >> cols;

		    pnt->r = rows;
		    pnt->c = cols;


		  //initializes the grid matrix
		  try{
			  pnt->matrix = new REAL8*[pnt->r];
		      for (UINT4 i=0; i < pnt->r; i++)
		    	 pnt->matrix[i] = new REAL8[pnt->c];
		      }catch(std::bad_alloc){cerr << "unable to allocate memory...";
		      cin.get(); exit(-1);}


		  //reads from the file and fills-in the matrix
		  for(UINT4 i = 0; i < pnt->r; i++)
		  {
		    for(UINT4 j = 0; j < pnt->c; j++)
		    {
		      input >> values;
		       if(input.eof())
		       {
		        cerr << "Unexpected end of file " << fname << endl;
		        exit(EXIT_FAILURE);
		       }
		      pnt->matrix[i][j] = values;
		    }
		  }

		  try{
		        if(input.is_open())
		        input.close();

		    }catch(const exception& e){

		      cerr << "Couldn't close file with message " << e.what() << endl;
		      exit(EXIT_FAILURE);

		    }
		    return EXIT_SUCCESS;
}
