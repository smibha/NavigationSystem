/*
 * CWaypoint.h
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include <string>

#define DECIMAL 1
#define DDMMSS 2

class CWaypoint {

public:

	CWaypoint(std::string name = "DefaultWPName", double latitude = 0, double longitude = 0); //since this constructor is provided compiler doesnt provide default constructor (constructor with no parameters)

	void set(std::string name, double latitude, double longitude);

	void getAllDataByPointer(std::string *pname, double *platitude, double *plongitude) const;

	void getAllDatabyReference(std::string &name, double &latitude, double &longitude) const;

	void print(uint8_t format) const;

	double calculateDistance(const CWaypoint &wp) const;

	CWaypoint& add(const CWaypoint &wp_right) const;

	bool less(const CWaypoint &wp_right) const;

	void setLatitude(const double latitude);

	void setLongitude(const double longitude);

	void setName(const std::string name);

	std::string getName() const;

	double getLatitude() const;

	double getLongitude() const;

private:

	std::string m_name;

	double m_latitude;

	double m_longitude;

//	bool m_valid;

	void transform2degmmss(int &deg, int &mm, double &ss) const;

};

#endif /* CWAYPOINT_H_ */
