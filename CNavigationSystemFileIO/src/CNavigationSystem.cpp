/*
 * CNavigationSystem.cpp
 *
 *  Created on: 13 Aug 2016
 *      Author: Smi u
 */

#include <iostream>

#include "CNavigationSystem.h"
#include "CIndentCodec.h"
#include "CCSVCodec.h"

CNavigationSystem::CNavigationSystem()
{
}

void CNavigationSystem::run()
{
	m_route.connectToPoiDatabase(&m_poiDatabase);

	unsigned short int enteredId;
	std::cout << "Make your choice - choose from 0 to 14 : " << std::endl;
	std::cout << "=======================================" << std::endl << std::endl;

	std::cout << " 1 - Read point of interests for POI database in indent file format." << std::endl;
	std::cout << " 2 - Read point of interests for POI database in CSV file format." << std::endl;
	std::cout << " 3 - Read point of interests for POI database in XML file format." << std::endl << std::endl;

	std::cout << " 4 - Read waypoints and point of interests for route in indent file format." << std::endl;
	std::cout << " 5 - Read waypoints and point of interests for route in CSV file format." << std::endl;
	std::cout << " 6 - Read waypoints and point of interests for route in XML file format." << std::endl << std::endl;

	std::cout << " 7 - Print the waypoints and point of interests in the route." << std::endl << std::endl;

	std::cout << " 8 - Find next POI for current GPS position from POI database." << std::endl << std::endl;

	std::cout << " 9 - Write point of interests from POI database in indent file format." << std::endl;
	std::cout << "10 - Write point of interests from POI database in CSV file format." << std::endl;
	std::cout << "11 - Write point of interests from POI database in XML file format." << std::endl << std::endl;

	std::cout << "12 - Write waypoints and point of interests from route in indent file format." << std::endl;
	std::cout << "13 - Write waypoints and point of interests from route in CSV file format." << std::endl;
	std::cout << "14 - Write waypoints and point of interests from route in XML file format." << std::endl << std::endl;

	std::cout << " 0 - Exit the program." << std::endl;
	std::cin >> enteredId;

	/*TODO implement above UI and to exit program only if 0 is pressed*/
	switch(enteredId)
	{
	case 0:	exit(0);
	case 1:
	{
		CCodec* basePointer = new CIndentCodec();
		m_route.readFromFile("inputIndent_1.txt", false, *basePointer);
		printRoute();
		break;
	}
	case 2:
	{
		printRoute();
		break;
	}
	case 3:
	{
		printDistanceCurPosNextPoi();
		break;
	}
	case 4:
	{
		CCodec* basePointer = new CIndentCodec();
		m_route.readFromFile("inputIndent_1.txt", true, *basePointer);
		m_route.writeToFile("outputIndent_1.txt", *basePointer);
		break;
	}
	case 5:
	{
		CCodec* basePointer = new CCSVCodec();
		m_route.readFromFile("inputCSV_1.txt", false, *basePointer);
		printRoute();
		break;
	}
	case 6:
	{
		CCodec* basePointer = new CCSVCodec();
		m_route.readFromFile("inputCSV_1.txt", true, *basePointer);
		m_route.writeToFile("outputCSV_1.txt", *basePointer);
		break;
	}
	default:
	{
		std::cout << "ERROR : Invalid input. Valid number is from 0 to 4 only. " << std::endl;
		break;
	}
	}
}

void CNavigationSystem::printRoute() const
{
	m_route.print();
}

void CNavigationSystem::printDistanceCurPosNextPoi() const
{
	CPOI poi; /*Temp object to hold nearest POI sent by CRoute.getDistanceNextPoi*/
	double dist = m_route.getDistanceNextPoi(m_GPSSensor.getCurrentPosition(), poi);
	std::cout << "Distance to the next point of interest is " << dist << " Kms " << std::endl;
	poi.print();
}
