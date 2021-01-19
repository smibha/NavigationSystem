/*
 * CPOI.h
 *
 *  Created on: 12 Aug 2016
 *      Author: Smi u
 */

#ifndef CPOI_H_
#define CPOI_H_

#include "CWaypoint.h"

enum t_poi{RESTAURANT, MUSEUM, WATERSPORTS, MOUNTAIN, PUB, THEATER, PARK, SEASIDE, PETROLSTATION, SUPERMARKET, NONE};

class CPOI : public CWaypoint {

public:

	CPOI(t_poi type = t_poi::NONE, std::string name = "DefaultPoi", std::string description = "DefaultDescription", double latitude = 0, double longitude = 0);

	void print() const;

	std::string getPoiType2String(t_poi poiTyp) const;

	void setDescription(const std::string &description);

	const std::string& getDescription() const;

	void setType(const t_poi type);

	const t_poi getType() const;

private:

	t_poi m_type;

	std::string m_description;

};

#endif
