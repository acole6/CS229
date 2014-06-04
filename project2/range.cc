#include "range.h"
#include "automatonparser.h"
#include <sstream>
#include <iostream>
#include <stdlib.h>

/**
 * Implementation of range.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets all values to 0.
 */
Range::Range()
{
	xStart = 0;
	xEnd = 0;
	yStart = 0;
	yEnd = 0;
}

/**
 * Takes in a range struct and sets the values
 * based on the values in the range struct.
 * @param rangeStruct 
 *				The string range struct.
 */
Range::Range(string rangeStruct)
{
	map<string, string> range = AutomatonParser::parse(rangeStruct);
	updateRange(AutomatonParser::getValue(range, "Xrange", true), AutomatonParser::getValue(range, "Yrange", true));
}

/**
 * Constructor that sets the range values to the given values.
 * @param xStart 
 *				The start of the x range.
 * @param xEnd 
 *				The end of the x range.
 * @param yStart 
 *				The start of the y range.
 * @param yEnd 
 *				The end of the y range.
 */
Range::Range(int xStart, int xEnd, int yStart, int yEnd)
{
	this->xStart = xStart;
	this->xEnd = xEnd;
	this->yStart = yStart;
	this->yEnd = yEnd;
}

/**
 * Copy constructor.
 * @param range
 *				The range to be copied.
 */
Range::Range(const Range &range)
{
	xStart = range.xStart;
	xEnd = range.xEnd;
	yStart = range.yStart;
	yEnd = range.yEnd;
}

/**
 * Destructor
 */
Range::~Range() {}

/**
 * Overloaded assignment operator.
 * @param range 
 *				The range to be copied.
 * @return 
 *				A copy of the given range.
 */
Range& Range::operator=(const Range &range)
{
	if(this == &range) return *this;
	xStart = range.xStart;
	xEnd = range.xEnd;
	yStart = range.yStart;
	yEnd = range.yEnd;
	return *this;
}

/**
 * Gets the xStart value.
 * @return 
 *			The value of xStart.
 */
int Range::getXStart()
{
	return xStart;
}

/**
 * Gets the xEnd value.
 * @return 
 *			The value of xEnd.
 */
int Range::getXEnd()
{
	return xEnd;
}

/**
 * Gets the yStart value.
 * @return 
 *			The value of yStart.
 */
int Range::getYStart() 
{
	return yStart;
}

/**
 * Gets the yEnd value.
 * @return 
 *			The value of yEnd.
 */
int Range::getYEnd()
{
	return yEnd;
}

/**
 * Creates a range string in the form of low..high.
 * @returns 
 *			A string representation of a range.
 */
string Range::rangeStr(int start, int end)
{
	ostringstream ret;
	ret << start << ".." << end;
	return ret.str();
}

/**
 * Sets the xStart value to the given value.
 * @param xStart 
 *			The value to be assigned.
 */
void Range::setXStart(int xStart)
{
	this->xStart = xStart;
}


/**
 * Sets the xEnd value to the given value.
 * @param xEnd 
 *			The value to be assigned.
 */
void Range::setXEnd(int xEnd)
{
	this->xEnd = xEnd;
}

/**
 * Sets the yStart value to the given value.
 * @param yStart 
 *			The value to be assigned.
 */
void Range::setYStart(int yStart)
{
	this->yStart = yStart;
}

/**
 * Sets the yEnd value to the given value.
 * @param yEnd 
 *			The value to be assigned.
 */
void Range::setYEnd(int yEnd)
{
	this->yEnd = yEnd;
}

/**
 * Update the range values with the given range strings.
 * @param rangeX 
 *			The x range string.
 * @param rangeY 
 *			The y range string.
 */
void Range::updateRange(string rangeX, string rangeY)
{
	if(!rangeX.empty()) //only updates if not empty
	{
		update(rangeX, xStart, xEnd);
	}

	if(!rangeY.empty())
	{
		update(rangeY, yStart, yEnd);
	}
}

/**
 * Creates a string range struct in the form of Type = { XRange = rangeX; YRange = rangeY; };
 * @param type 
 *			The name of the range.
 * @return 
 *			A string representation of range struct.
 */
string Range::toString(string type)
{
	ostringstream ret;
	ret << type << " = {\n\t\tXrange = " << rangeStr(xStart, xEnd) << ";\n\t\tYrange = " << rangeStr(yStart, yEnd) << ";\n\t};";
	return ret.str();
}

/**
 * Updates the start and end value of the given range.
 * @param range 
 *			The string representation of the range.
 * @param start 
 *			The start range value to be updated.
 * @param end 
 *			The end range value to be updated.
 * @throws InvalidRangeException
 *			If at least one of the ranges is invalid or if start is greater than end.
 */
void Range::update(string range, int &start, int &end)
{
	string temp = range;
	int dotIndex = temp.find(".");
	if(dotIndex == string::npos) //if no dots, the range is invalid
	{
		cerr << "Invalid range: " << range << endl;
		throw InvalidRangeException;
	}
	string low = temp.substr(0, dotIndex);
	
	temp = temp.substr(dotIndex + 1, temp.length());
	dotIndex = temp.find(".");
	if(dotIndex == string::npos) //if no dots, the range is invalid
	{
		cerr << "Invalid range: " << range << endl;
		throw InvalidRangeException;
	}
	string high = temp.substr(dotIndex + 1, temp.length());

	start = atoi(low.c_str());
	end = atoi(high.c_str());
	if(start > end) //if the start value is greater than the end value, the range is invalid
	{
		cerr << "Invalid range: " << range << ";low: " << start << ";high: " << end << endl;
		throw InvalidRangeException;
	}
}
