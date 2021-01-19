/*
 * CPoiDatabase.h
 *
 *  Created on: 12 Aug 2016
 *      Author: Smi u
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_

#include <map>

#include "CPOI.h"

class CPoiDatabase {

public:

	CPoiDatabase();

	void addPoiToDb(t_poi type, std::string name, std::string description, double latitude, double longitude);

	void clearPoisFromDb();

	const CPOI* getPointerToPoiFromDb(std::string name) const;

	void printDb() const;

private:

	std::map<std::string, CPOI> m_Poi;

};

#endif /* CPOIDATABASE_H_ */
