/*
 * RenameFile.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: Marco.Maneta
 */

#include<errno.h>
#include "Report.h"

int Report::RenameFile(string oldname){


	remove(oldname.c_str());
	if(errno != 0 && errno != 2)
	{
		cout << errno << " " << oldname;
		perror("error");
		throw (EXIT_FAILURE);
	}
	rename(oldname.c_str(), (oldname + ".old").c_str());
	if(errno != 0 && errno != 2)
	{
		cout << errno << " " << oldname;
		perror("Error creating backup .old file");
		throw (EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
