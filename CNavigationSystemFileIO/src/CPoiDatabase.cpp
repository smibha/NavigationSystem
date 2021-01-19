/*
 * CPoiDatabase.cpp
 *
 *  Created on: 12 Aug 2016
 *      Author: Smi u
 */
#include <iostream>

#include "CPoiDatabase.h"

CPoiDatabase::CPoiDatabase()
{
}

void CPoiDatabase::addPoiToDb(t_poi type, std::string name, std::string description, double latitude, double longitude)
{
	CPOI temp(type, name, description, latitude, longitude);
	std::pair<std::map<std::string, CPOI>::iterator, bool> exist;
	exist = m_Poi.insert(std::pair<std::string, CPOI> (name, temp));

	/* Added element already exists with the specified name and CPOI has to be updated */
	if(exist.second == false) {
		std::map<std::string, CPOI>::iterator it = m_Poi.find(name);
		it->second = temp;
	}
}

const CPOI* CPoiDatabase::getPointerToPoiFromDb(std::string name) const
{
	std::map<std::string, CPOI>::const_iterator it = m_Poi.find(name);
	if(it != m_Poi.end())
	{
		return (&(it->second));
	}
	else
	{
		std::cout << "ERROR : There is no point of interest with the name, " << name << " in POI Database." << std::endl;
		return 0;
	}
}

void CPoiDatabase::clearPoisFromDb()
{
	m_Poi.clear();
}

void CPoiDatabase::printDb() const
{
	std::map<std::string, CPOI>::const_iterator it;
	for (it = m_Poi.begin(); it != m_Poi.end(); it++)
	{
		it->second.print();
	}
}

