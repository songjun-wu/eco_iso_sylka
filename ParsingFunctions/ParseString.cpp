/*
 * ParseString.cpp
 *
 *  Created on: Oct 12, 2009
 *      Author: Marco Maneta
 */

#include "ParsingFunctions.h"

string ParseString(string FileRoot, int TimeStep)
{
    string S = "0000000000";
    std::stringstream ss;
    ss << TimeStep;
    string time = ss.str();
    S.insert(0, FileRoot);
    S.erase(FileRoot.length()+1, FileRoot.length());
    int length = S.length();
    S.insert((length-time.length()+1), time);
    length = S.length();
    S.erase(S.length()-time.length()+1, time.length());
    S.insert(S.length()-3, ".");

    return S;
}
