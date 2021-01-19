/*
 * CNavigationSystem.h
 *
 *  Created on: 13 Aug 2016
 *      Author: Smi u
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"

class CNavigationSystem {

public:

	CNavigationSystem();

	void run();

private:

	CGPSSensor m_GPSSensor;

	CRoute m_route;

	CPoiDatabase m_poiDatabase;

	void printRoute() const;

	void printDistanceCurPosNextPoi() const;

};




#endif /* CNAVIGATIONSYSTEM_H_ */
