#ifndef RANGE_H
#define RANGE_H

#include <string>

using namespace std;

const int InvalidRangeException = 10;

/**
 * class that represents a range between low and high value
 * @author Alex Cole
 */
class Range 
{
	/**
	 * low x range value
	 */
	int xStart;

	/**
	 * high x range value
	 */
	int xEnd;

	/**
	 * low y range value
	 */
	int yStart;

	/**
	 * high y range value
	 */
	int yEnd;

public:
	/**
	 * Default constructor that sets all values to 0.
	 */
	Range();

	/**
	 * Takes in a range struct and sets the values
	 * based on the values in the range struct.
	 * @param rangeStruct 
	 *				The string range struct.
	 */
	Range(string rangeStruct);

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
	Range(int xStart, int xEnd, int yStart, int yEnd);

	/**
	 * Copy constructor.
	 * @param range
	 *				The range to be copied.
	 */
	Range(const Range &range);

	/**
	 * Destructor
	 */
	~Range();

	/**
	 * Overloaded assignment operator.
	 * @param range 
	 *				The range to be copied.
	 * @return 
	 *				A copy of the given range.
	 */
	Range& operator=(const Range &range);

	/**
	 * Gets the xStart value.
	 * @return 
	 *			The value of xStart.
	 */
	int getXStart();

	/**
	 * Gets the xEnd value.
	 * @return 
	 *			The value of xEnd.
	 */
	int getXEnd();

	/**
	 * Gets the yStart value.
	 * @return 
	 *			The value of yStart.
	 */
	int getYStart();

	/**
	 * Gets the yEnd value.
	 * @return 
	 *			The value of yEnd.
	 */
	int getYEnd();

	/**
	 * Creates a range string in the form of low..high.
	 * @returns 
	 *			A string representation of a range.
	 */
	string rangeStr(int start, int end);

	/**
	 * Sets the xStart value to the given value.
	 * @param xStart 
	 *			The value to be assigned.
	 */
	void setXStart(int xStart);

	/**
	 * Sets the xEnd value to the given value.
	 * @param xEnd 
	 *			The value to be assigned.
	 */
	void setXEnd(int xEnd);

	/**
	 * Sets the yStart value to the given value.
	 * @param yStart 
	 *			The value to be assigned.
	 */
	void setYStart(int yStart);

	/**
	 * Sets the yEnd value to the given value.
	 * @param yEnd 
	 *			The value to be assigned.
	 */
	void setYEnd(int yEnd);

	/**
	 * Update the range values with the given range strings.
	 * @param rangeX 
	 *			The x range string.
	 * @param rangeY 
	 *			The y range string.
	 */
	void updateRange(string rangeX, string rangeY);

	/**
	 * Creates a string range struct in the form of Type = { XRange = rangeX; YRange = rangeY; };
	 * @param type 
	 *			The name of the range.
	 * @return 
	 *			A string representation of range struct.
	 */
	string toString(string type);

private:
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
	void update(string range, int &start, int &end);
};

#endif
