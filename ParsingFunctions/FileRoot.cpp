/*
 * FileRoot.cpp
 *
 *  Created on: Oct 12, 2009
 *      Author: Marco Maneta
 */

#include <string.h>
#include "ParsingFunctions.h"

string FileRoot(string S)
{
    char p[512];
    int k;
    S.erase(S.find('.'), 4);
    strcpy (p, S.c_str());
    k = S.length();
    while(p[k-1]>='0' && p[k-1]<='9') {
      S.erase(k,1);
      k--;
    }
    return S;
}
