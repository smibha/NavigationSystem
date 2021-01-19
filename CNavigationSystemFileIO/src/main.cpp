/*
 * main.cpp
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */
#include <iostream>
#include <stdlib.h>

#include "CNavigationSystem.h"

int main (void)
{
	std::cout << "========================================================================================" << std::endl;
	std::cout << "                              Navigation System Application                             " << std::endl;
	std::cout << "========================================================================================" << std::endl << std::endl;

	std::cout << "Navigation System Application provides route and point of interest database." << std::endl;
	std::cout << "Waypoints and point of interests can be added to the route. Point of interests in" << std::endl;
	std::cout << "route is linked to route by searching for the correspoinding POI in POI database." << std::endl;
	std::cout << "The waypoints and point of interests for route, and point of interests to database" << std::endl;
	std::cout << "is provided by different file formats - Indent, CSV and XML." << std::endl << std::endl;

//	int *a, *b;
//	int result; a = new(int); //Missing: b = new(int);
//	*a = 5;
//	*b = 7;
//	result = *a + *b;
//	std::cout << "Result = " << result << std::endl;
//
//	int ar[3]; ar[3] = 5; ar[10] = 7; std::cout << "ar[3]=" << ar[3] << "ar[10]" << ar[10] << std::endl;


	CNavigationSystem navSys;
	navSys.run();
	return 0;
}
