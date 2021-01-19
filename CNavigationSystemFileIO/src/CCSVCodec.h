/*
 * CCSVCodec.h
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */

#ifndef MYCODE_CCSVCODEC_H_
#define MYCODE_CCSVCODEC_H_

#include "CCodec.h"

class CCSVCodec: public CCodec
{

public:

	CCSVCodec();

	virtual ~CCSVCodec();

	virtual void write(std::ostream& stream, const std::vector<CWaypoint>& waypoints, const std::vector<const CPOI*>& pois) const;

	virtual void read(std::vector<CWaypoint>& waypoints, std::vector<CPOI>& pois, std::istream& stream) const;

};

#endif /* MYCODE_CCSVCODEC_H_ */
