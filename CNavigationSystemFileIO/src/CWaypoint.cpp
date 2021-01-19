/*
* CWaypoint.cpp
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */
#include <iostream>
#include <math.h>

#include "CWaypoint.h"

#define R 6378
#define DEG2RAD 0.01746031746031746L

CWaypoint::CWaypoint(std::string name, double latitude, double longitude) :
m_name(name),
m_latitude(latitude),
m_longitude(longitude)
//m_valid(false)
{
	set(name, latitude, longitude);
}

void CWaypoint::set(std::string name, double latitude, double longitude)
{
	m_name = name;
	if ((latitude >= -90) && (latitude <= 90))
	{
		m_latitude = latitude;
//		m_valid = true;
	}
	else
		m_latitude = 0;
	if ((longitude >= -180) && (longitude <= 180))
	{
		m_longitude = longitude;
//		m_valid = true;
	}
	else
		m_longitude = 0;
}

std::string CWaypoint::getName() const
{
	return m_name;
}

double CWaypoint::getLatitude() const
{
	return m_latitude;
}

double CWaypoint::getLongitude() const
{
	return m_longitude;
}

void CWaypoint::getAllDataByPointer(std::string* pname, double* platitude, double* plongitude) const
{
	*pname = m_name;
	*platitude = m_latitude;
	*plongitude = m_longitude;
}

void CWaypoint::getAllDatabyReference(std::string& name, double& latitude, double& longitude) const
{
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
}

void CWaypoint::transform2degmmss(int& deg, int& mm, double& ss) const
{
	deg = (int)m_latitude;
	mm = (int)((m_latitude - (double)deg)*60);
	ss = (((m_latitude - deg)*60) - mm) * 60;
}

void CWaypoint::print(uint8_t format) const
{
	if (format == 1)
	{
		std::cout << "Printing in decimal format : " << std::endl;
		std::cout << "-----------------------------" << std::endl;
		std::cout << "Name			: " << m_name << std::endl;
		std::cout << "Latitude		: " << m_latitude << std::endl;
		std::cout << "Longitude		: " << m_longitude << std::endl << std::endl;
	}
	else if(format == 2)
	{
		int d_lat, m_lat, d_long, m_long;
		double s_lat, s_long;
		transform2degmmss(d_lat, m_lat, s_lat);
		transform2degmmss(d_long, m_long, s_long);
		std::cout << "Printing in degree minutes seconds format : " << std::endl;
		std::cout << "--------------------------------------------" << std::endl;
		std::cout << "Name			: " << m_name << std::endl;
		std::cout << "Latitude		: " << d_lat << " degree " << m_lat << " minutes " << s_lat << " seconds" << std::endl;
		std::cout << "Latitude		: " << d_long << " degree " << m_long << " minutes " << s_long << " seconds" << std::endl << std::endl;
	}
	else
		std::cout << "ERROR : Wrong input format." << std::endl;
}

double CWaypoint::calculateDistance(const CWaypoint& wp) const
{
	return (R*acos(sin(m_latitude*DEG2RAD)*sin(wp.m_latitude*DEG2RAD)+cos(m_latitude*DEG2RAD)*cos(wp.m_latitude*DEG2RAD)*cos((wp.m_longitude-m_longitude)*DEG2RAD)));
}

CWaypoint& CWaypoint::add(const CWaypoint& wp_right) const
{
	CWaypoint temp;
	std::string temp_name;
	double temp_lat, temp_long;
	temp_name = m_name + wp_right.m_name;
	temp_lat = m_latitude + wp_right.m_latitude;
	temp_long = m_longitude + wp_right.m_longitude;
	temp.set(temp_name, temp_lat, temp_long);
	return temp;
}

bool CWaypoint::less(const CWaypoint& wp_right) const
{
	CWaypoint equator("Equator", 0, 0);
	std::cout << "Distance from equator :" << std::endl;
	std::cout << "-----------------------" << std::endl;
	if ((calculateDistance(equator)) < (equator.calculateDistance(wp_right)))
	{
		std::cout << m_name << " < " << wp_right.m_name << std::endl;
		return true;
	}
	else
	{
		std::cout << m_name << " > " << wp_right.m_name << std::endl;
		return false;
	}
}

void CWaypoint::setLatitude(const double latitude)
{
	if ((latitude >= -90) && (latitude <= 90))
	{
		m_latitude = latitude;
//		m_valid = true;
	}
	else
		m_latitude = 0;
}

void CWaypoint::setLongitude(const double longitude)
{
	if ((longitude >= -180) && (longitude <= 180))
	{
		m_longitude = longitude;
//		m_valid = true;
	}
	else
		m_longitude = 0;
}

void CWaypoint::setName(const std::string name)
{
	m_name = name;
}
