/*
 * CGPSSensor.cpp
 *
 *  Created on: 13 Aug 2016
 *      Author: Smi u
 */

#include <iostream>

#include "CGPSSensor.h"

CGPSSensor::CGPSSensor()
{
}

CWaypoint& CGPSSensor::getCurrentPosition() const
{
	std::cout << "GPS Sensor : " << std::endl;
	std::cout << "-------------" << std::endl;
	double latitude, longitude;
	std::cout << "Enter the current latitude :" << std::endl;
	std::cin >> latitude;
	std::cout << "Enter current longitude : " << std::endl;
	std::cin >> longitude;
	CWaypoint temp;
	temp.set("GPS_Sensor_Location", latitude, longitude);
	return temp;
}
