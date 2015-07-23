/*
 * Grid.h
 *
 *  Created on: May 21, 2009
 *      Author: Marco Maneta (maco.maneta@umontana.edu)
 *
 *      This file contains the new grid data structure that will be used to solve
 *      the kinematic wave. The grid structure dynamically creates a 2D array. A
 *      copy constructor and overloaded operators are implemented to permit easier
 *      initialization and manipulation of the grids.
 *
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include "csf.h" //pcraster I/O functions
using namespace std;


struct grid{

    REAL8 **matrix;
    UINT4 r, c;
    REAL8 north, south, east, west, dx, nodata;

    //ctor
    grid(UINT4 row, UINT4 cols);

    //ctor form grass raster ascii file
    grid(std::string fname, std::string type);

    //copy ctor
    grid(const grid &m);

    //reset array to zero
    void reset();

    int writeASCIIMap(std::string fname);

    //PCRaster input and output options
    int PCRMap2grid(std::string fname);
    int grid2PCRMap(std::string fname,
                            CSF_CR cellRepr,
                            CSF_VS dataType);

     //inline operator overload (=,+,-,+=,-=,==,!=)

    grid& operator=(const grid &m);

    grid operator+(const grid &m);

    grid operator-(const grid &m);

    grid& operator+=(const grid &m);

    grid& operator-=(const grid &m);

    bool operator==(const grid&b) const;

    bool operator!=(const grid&b) const;

    grid createLDD ();

    //dtor
    ~grid();

};

#endif /* GRID_H_ */
