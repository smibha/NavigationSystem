/*
 * CRoute.h
 *
 *  Created on: 12 Aug 2016
 *      Author: Smi u
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include <vector>

#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CCodec.h"

class CRoute {

public:

	CRoute();

	~CRoute();

	void connectToPoiDatabase(CPoiDatabase *pPoiDB);

	void addWaypoint(const CWaypoint &wp);

	void addPoiToRoute(std::string namePoi);

	double getDistanceNextPoi(const CWaypoint &wp, CPOI &poi) const;

	void print() const;

	void writeToFile(std::string filename, const CCodec& coder) const;

	void readFromFile(std::string filename, bool deleteOldData, const CCodec& coder);

private:

	std::vector<CWaypoint> m_waypoints;

	std::vector<const CPOI*> m_pois;

	CPoiDatabase* m_pPoiDatabase;

};

#endif /* CROUTE_H_ */
