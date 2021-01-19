/*
 * CRoute.cpp
 *
 *  Created on: 12 Aug 2016
 *      Author: Smi u
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "CRoute.h"

CRoute::CRoute()
{
	m_pPoiDatabase = 0;
}

CRoute::~CRoute()
{
}

void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	m_pPoiDatabase = pPoiDB;
}

void CRoute::addWaypoint(const CWaypoint& wp)
{
	m_waypoints.push_back(wp);
}

void CRoute::addPoiToRoute(std::string namePoi)
{
	if (m_pPoiDatabase != 0)
	{
		if (m_pPoiDatabase->getPointerToPoiFromDb(namePoi) != 0)
			m_pois.push_back(m_pPoiDatabase->getPointerToPoiFromDb(namePoi));
		else
			std::cerr << "ERROR : POI with specified is not found in database, and therefore not added to route." << std::endl;
	}
}

/*Get nearest POI along with distance from a given point of location*/
double CRoute::getDistanceNextPoi(const CWaypoint& wp, CPOI& poi) const
{
	double nearestPoi = m_pois[0]->calculateDistance(wp), temp;
	unsigned short pos = 0;
	for (unsigned short int i = 0; i != m_pois.size(); ++i)
	{
		if (nearestPoi > (temp = m_pois[i]->calculateDistance(wp)))
		{
			nearestPoi = temp;
			pos = i;
		}
	}
	poi = *m_pois[pos]; /*Call by reference- directly update the CPoi object by reference*/
	return (nearestPoi);
}

void CRoute::print() const
{
	std::cout << "Waypoints in the route : " << std::endl;
	std::cout << "======================== " << std::endl;
	for (std::vector<CWaypoint>::const_iterator it = m_waypoints.begin(); it != m_waypoints.end(); ++it)
	{
		it->print(DECIMAL);
	}
	std::cout << std::endl << std::endl;
	std::cout << "Point of interests in the route : " << std::endl;
	std::cout << "================================= " << std::endl;
	for (std::vector<const CPOI*>::const_iterator it = m_pois.begin(); it != m_pois.end(); ++it)
	{
		(*it)->print();
	}
}

void CRoute::readFromFile(std::string filename, bool deleteOldData, const CCodec& coder)
{
	/*TODO add exceptions to ifstream n ofstream*/
	std::ifstream inFileStream;
	inFileStream.open(filename.c_str());
	if(deleteOldData)
	{
		m_waypoints.clear();
		m_pPoiDatabase->clearPoisFromDb();
	}
	std::vector<CWaypoint> temp_wps;
	std::vector<CPOI> temp_pois;
	coder.read(temp_wps, temp_pois, inFileStream);
	for(std::vector<CWaypoint>::iterator itr = temp_wps.begin(); itr != temp_wps.end(); itr++)
	{
		m_waypoints.push_back(*itr);
	}
	for(std::vector<CPOI>::iterator it = temp_pois.begin(); it != temp_pois.end(); it++)
	{
		m_pPoiDatabase->addPoiToDb((*it).getType(), (*it).getName(), (*it).getDescription(), (*it).getLatitude(), (*it).getLongitude());
		addPoiToRoute((*it).getName());
	}
}

void CRoute::writeToFile(std::string filename, const CCodec& coder) const
{
	std::ofstream outFileStream;
	outFileStream.open(filename.c_str());
	coder.write(outFileStream, m_waypoints, m_pois);
}
