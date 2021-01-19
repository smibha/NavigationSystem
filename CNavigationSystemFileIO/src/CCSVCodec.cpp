/*
 * CCSVCodec.cpp
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */

#include "CCSVCodec.h"

namespace helper
{
	static std::string cutLeft(std::string& line)
	{
		size_t loc = line.find_first_of(";\r");
		std::string temp = line.substr(0, loc);
		line = line.substr(loc+1);
		return temp;
	}

	t_poi string2Enum(const std::string& type);
}

CCSVCodec::CCSVCodec()
{

}

CCSVCodec::~CCSVCodec()
{

}

void CCSVCodec::write(std::ostream &stream,
		const std::vector<CWaypoint> &waypoints,
		const std::vector<const CPOI*> &pois) const
{
	std::vector<CWaypoint>::const_iterator it;
	for (it = waypoints.begin(); it != waypoints.end(); ++it)
	{
		stream << "WP;" << (*it).getName() << ";" << (*it).getLatitude() << ";" << (*it).getLongitude() << ";" << std::endl;
	}

	std::vector<const CPOI*>::const_iterator itr;
	for (itr = pois.begin(); itr != pois.end(); ++itr)
	{
		stream << "POI;" << (*(*itr)).getName()  << ";" << (*(*itr)).getType() << ";" << (*(*itr)).getDescription() << ";" << (*(*itr)).getLatitude() << ";" << (*(*itr)).getLongitude() << std::endl;
	}
}

void CCSVCodec::read(std::vector<CWaypoint> &waypoints, std::vector<CPOI> &pois,
		std::istream &stream) const
{
	std::string text, keyword, value;
	int lineNumber = 0;
//	state_machine state = state_machine::Idle;
//	bool objTypeWP = false;
//	waypoints.clear();
//	pois.clear();

	CPOI temp;

	while (!(stream.eof()))
	{
		std::getline(stream, text);
		lineNumber++;
		std::string slicedText = helper::cutLeft(text);
		/*TODO Implement case insensitive checking*/
		if(slicedText == "WP")
		{
			std::string name = helper::cutLeft(text);
			double lat = atof(helper::cutLeft(text).c_str());
			double lon = atof(helper::cutLeft(text).c_str());
			waypoints.push_back(CWaypoint(name, lat, lon));
		}
		else if(slicedText == "POI")
		{
			std::string name = helper::cutLeft(text);
			std::string description = helper::cutLeft(text);
			t_poi type  = helper::string2Enum(helper::cutLeft(text));
			double lat = atof(helper::cutLeft(text).c_str());
			double lon = atof(helper::cutLeft(text).c_str());
			pois.push_back(CPOI(type, name, description, lat, lon));
		}
	}
}
