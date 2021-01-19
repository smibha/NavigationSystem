/*
 * CCodec.h
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */

#ifndef MYCODE_CCODEC_H_
#define MYCODE_CCODEC_H_

#include <ostream>
#include <istream>
#include <vector>

#include "CWaypoint.h"
#include "CPOI.h"

enum state_machine {Idle, RecordStarted, KeywordRead, ValueLineRead};

class CCodec
{
public:

	virtual void write(std::ostream& stream, const std::vector<CWaypoint>& waypoints, const std::vector<const CPOI*>& pois) const = 0;

	virtual void read(std::vector<CWaypoint>& waypoints, std::vector<CPOI>& pois, std::istream& stream) const = 0;

	virtual ~CCodec() {}

};

#endif /* MYCODE_CCODEC_H_ */
