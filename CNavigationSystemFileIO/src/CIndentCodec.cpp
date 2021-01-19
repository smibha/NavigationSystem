/*
 * CIndentCodec.cpp
 *
 *  Created on: 7 Aug 2016
 *      Author: Smi u
 */

#include <iostream>
#include <sstream>

#include "CIndentCodec.h"

namespace helper
{

t_poi string2Enum(const std::string& type)
{
	if (type == "RESTAURANT")
	{
		return t_poi::RESTAURANT;
	}
	else if (type == "MUSUEM")
	{
		return t_poi::MUSEUM;
	}
	else if (type == "WATERSPORTS")
	{
		return t_poi::WATERSPORTS;
	}
	else if (type == "MOUNTAIN")
	{
		return t_poi::MOUNTAIN;
	}
	else if (type == "PUB")
	{
		return t_poi::PUB;
	}
	else if (type == "THEATER")
	{
		return t_poi::THEATER;
	}
	else if (type == "PARK")
	{
		return t_poi::PARK;
	}
	else if(type == "SEASIDE")
	{
		return t_poi::SEASIDE;
	}
	else if(type == "PETROLSTATION")
	{
		return t_poi::PETROLSTATION;
	}
	else if(type == "SUPERMARKET")
	{
		return t_poi::SUPERMARKET;
	}
	else
		throw "ERROR : Wrong Type for POI.";
}

static bool setKeywordValuePair(CPOI& temp, std::string keyword, std::string value, bool obj)
{
	if (obj == true)
	{
		if (keyword == "name")
		{
			temp.setName(value);
			return true;
		}
		else if (keyword == "latitude")
		{
			temp.setLatitude(atof(value.c_str()));
			return true;
		}
		else if (keyword == "longitude")
		{
			temp.setLongitude(atof(value.c_str()));
			return true;
		}
		else
		{
			std::cerr << "ERROR : Incorrect keyword provided for waypoint." << std::endl;
			return false;
		}
	}
	else
	{
		if (keyword == "name")
		{
			temp.setName(value);
			return true;
		}
		else if (keyword == "latitude")
		{
			temp.setLatitude(atof(value.c_str()));
			return true;
		}
		else if (keyword == "longitude")
		{
			temp.setLongitude(atof(value.c_str()));
			return true;
		}
		else if (keyword == "type")
		{
			try
			{
				temp.setType(helper::string2Enum(value));
			}
			catch(std::string& err)
			{
				std::cout << err << std::endl;
				return false;
			}
			return true;
		}
		else if (keyword == "description")
		{
			temp.setDescription(value);
			return true;
		}
		else
		{
			std::cerr << "ERROR : Incorrect keyword provided for POI." << std::endl;
			return false;
		}
	}
}

static void processRecord(CPOI& temp, bool objType, std::vector<CWaypoint>& waypoints, std::vector<CPOI>& pois)
{
	if (objType == true)
	{
		waypoints.push_back(static_cast<CWaypoint>(temp));
	}
	else
	{
		pois.push_back(temp);
	}
}

}

CIndentCodec::CIndentCodec()
{
}

CIndentCodec::~CIndentCodec()
{
}

void CIndentCodec::write(std::ostream& stream, const std::vector<CWaypoint>& waypoints, const std::vector<const CPOI*>& pois) const
{
	std::vector<CWaypoint>::const_iterator it;
	for (it = waypoints.begin(); it != waypoints.end(); ++it)
	{
		stream << "WP" << std::endl;
		stream << "	name" << std::endl;
		stream << "		" << (*it).getName() << std::endl;
		stream << "	latitude" << std::endl;
		stream << "		" << (*it).getLatitude() << std::endl;
		stream << "	longitude" << std::endl;
		stream << "		" << (*it).getLongitude() << std::endl;
		stream << std::endl;
	}

	std::vector<const CPOI*>::const_iterator itr;
	for (itr = pois.begin(); itr != pois.end(); ++itr)
	{
		stream << "POI" << std::endl;
		stream << "	name" << std::endl;
		stream << "		" << (*(*itr)).getName() << std::endl;
		stream << "	type" << std::endl;
		stream << "		" << (*(*itr)).getType() << std::endl;
		stream << "	description" << std::endl;
		stream << "		" << (*(*itr)).getDescription() << std::endl;
		stream << "	latitude" << std::endl;
		stream << "		" << (*(*itr)).getLatitude() << std::endl;
		stream << "	longitude" << std::endl;
		stream << "		" << (*(*itr)).getLongitude() << std::endl;
		stream << std::endl;
	}
}

/*TODO - do not store wp r poi if an attribute or val of att is absent - check setKeywordValue func, if its false, set state to idle*/
/*TODO replace all cout by cerr for error output */
/*TODO - if there is missing keyword, do not process record - use bit manipulation to implement this */
void CIndentCodec::read(std::vector<CWaypoint>& waypoints, std::vector<CPOI>& pois, std::istream& stream) const
{
	std::string text, keyword, value;
	uint8_t indent = 0, keywordIndent = 0, valueIndent = 0;
	int lineNumber = 0;
	state_machine state = state_machine::Idle;
	bool objTypeWP = false;
//	waypoints.clear();
//	pois.clear();

	CPOI temp;

	while (!(stream.eof()))
	{
		std::getline(stream, text);
		lineNumber++;
		switch (state)
		{
		case Idle:
		{
			if(text.find_first_not_of(" \t") != std::string::npos)
			{
				indent = text.find_first_not_of(" \t");
				if(text.find_last_not_of(" \r\n\t\f\v") ==  std::string::npos)
				{
					continue;
				}
				text = text.substr(0, text.find_last_not_of(" \r\n\t\f\v")+1);
				if (indent == 0)
				{
					if (text == "WP")
					{
						objTypeWP = true;
						state = RecordStarted;
					}
					else if(text == "POI")
					{
						objTypeWP = false;
						state = RecordStarted;
					}
					else
					{
						std::cerr << "ERROR : Wrong title in line number " << lineNumber << ". Title of the record should be only WP or POI " << std::endl;
					}
				}
				else
				{
					std::cerr << "ERROR : Indent for the title is not 0 in line number " << lineNumber << std::endl;
				}
			}
			break;
		}
		case RecordStarted:
		{
			if(text.find_first_not_of(" \t") != std::string::npos)
			{
				indent = text.find_first_not_of(" \t");
				if (indent > 0)
				{
					keywordIndent = indent;
					std::istringstream iss_keyword(text);
					iss_keyword >> keyword; // trims all white spaces
					state = KeywordRead;
				}
				else
				{
					std::cerr << "ERROR : Improper indent, expected indent > 0 in line number " << lineNumber << std::endl;
				}
			}
			break;
		}
		case KeywordRead:
		{
			if(text.find_first_not_of(" \t") != std::string::npos)
			{
				indent = text.find_first_not_of(" \r\n\t\f\v");
				if (indent > keywordIndent)
				{
					valueIndent = indent;
					if(text.find_last_not_of(" \r\n\t\f\v") ==  std::string::npos)
					{
						continue;
					}
					value = text.substr(indent, text.find_last_not_of(" \r\n\t\f\v")-(indent-1));
					state = ValueLineRead;
				}
				else
				{
					std::cerr << "ERROR : Improper indent in line number " << lineNumber << std::endl;
				}
			}
			break;
		}
		case ValueLineRead:
		{
			if(text.find_first_not_of(" \t") != std::string::npos)
			{
				indent = text.find_first_not_of(" \t");
				if (indent >= valueIndent)
				{
					if(text.find_last_not_of(" \r\n\t\f\v") ==  std::string::npos)
					{
						continue;
					}
					std::string loc_value  = text.substr(indent, text.find_last_not_of(" \r\n\t\f\v")-(indent-1));
					value = value + " " + loc_value;
					state = ValueLineRead;
					break;
				}
				else if ((indent < valueIndent) && (indent > 0))
				{
					if(!helper::setKeywordValuePair(temp, keyword, value, objTypeWP))
					{
						state = Idle;
						break;
					}
					keywordIndent = indent;
					if(text.find_last_not_of(" \r\n\t\f\v") ==  std::string::npos)
					{
						continue;
					}
					std::string loc_keyword  = text.substr(indent, text.find_last_not_of(" \r\n\t\f\v")-(indent-1));
					keyword = loc_keyword;
					state = KeywordRead;
					break;
				}
			}
			if(helper::setKeywordValuePair(temp, keyword, value, objTypeWP))
			{
				helper::processRecord(temp, objTypeWP, waypoints, pois);
			}
			state = Idle;
			break;
		}
		}
	}
}

