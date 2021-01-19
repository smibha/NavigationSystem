/*
 * CPOI.cpp
 *
 *  Created on: 12 Aug 2016
 *      Author: Smi u
 */

#include <iostream>

#include "CPOI.h"

CPOI::CPOI(t_poi type, std::string name, std::string description, double latitude, double longitude) : CWaypoint(name, latitude, longitude)
{
	m_type = type;
	m_description = description;
}

void CPOI::print() const
{
	CWaypoint::print(DECIMAL); /* Since both classes have same method name explicitly we have to mention */
	std::cout << "Type			: " << getPoiType2String(m_type) << std::endl;
	std::cout << "Description		: " << m_description << std::endl << std::endl;
}

const t_poi CPOI::getType() const
{
	return m_type;
}

std::string CPOI::getPoiType2String(t_poi poiTyp) const
{
	switch (poiTyp)
	{
	case t_poi::RESTAURANT:
		return "RESTAURANT";
		break;
	case t_poi::MUSEUM:
		return "MUSEUM";
		break;
	case t_poi::WATERSPORTS:
		return "WATERSPORTS";
		break;
	case t_poi::MOUNTAIN:
		return "MOUNTAIN";
		break;
	case t_poi::PUB:
		return "PUB";
		break;
	case t_poi::THEATER:
		return "THEATER";
		break;
	case t_poi::PARK:
		return "PARK";
		break;
	case t_poi::SEASIDE:
		return "SEASIDE";
		break;
	case t_poi::PETROLSTATION:
		return "PETROLSTATION";
		break;
	case t_poi::SUPERMARKET:
		return "SUPERMARKET";
		break;
	default:
		return "Wrong type of POI";
		break;
	}
}

const std::string& CPOI::getDescription() const
{
	return m_description;
}

void CPOI::setDescription(const std::string &description)
{
	m_description = description;
}

void CPOI::setType(const t_poi type)
{
	m_type = type;
}
