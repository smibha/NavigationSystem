/*
 * CGPSSensor.h
 *
 *  Created on: 13 Aug 2016
 *      Author: Smi u
 */

#ifndef CGPSSENSOR_H_
#define CGPSSENSOR_H_

#include "CWaypoint.h"

class CGPSSensor {

public:

	CGPSSensor();

	CWaypoint& getCurrentPosition() const;
};

#endif /* CGPSSENSOR_H_ */
