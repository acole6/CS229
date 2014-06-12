#include "colors.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of colors.h
 * @author Alex Cole
 */

/**
 * Default constructor. Sets the default
 * color with all 0 values.
 */
Colors::Colors() {}

/**
 * Constructs with a string representation of a colors struct.
 * @param colorStruct 
 *				The string colors struct.
 */
Colors::Colors(string colorsStruct) {}

/**
 * Constructs with given default color value.
 * @param defalutCl 
 *				The default color.
 */
Colors::Colors(Color defaultCl)
{
	this->defaultCl.setColor(defaultCl.getColor());
}

/**
 * Copy constructor.
 * @param colors 
 *				The colors to be copied.
 */
Colors::Colors(const Colors &colors)
{
	defaultCl = colors.defaultCl;
}

/**
 * Destructor
 */
Colors::~Colors() {}

/**
 * Overloaded assignment operator.
 * @param colors 
 *				The colors to be copied.
 * @return 
 *				A copy of given colors.
 */
Colors& Colors::operator=(const Colors &colors)
{
	if(this == &colors) return *this;
	defaultCl = colors.defaultCl;
	return *this;
}

/**
 * Gets the default color.
 * @return 
 *				A pointer to default color.
 */
Color* Colors::getDefaultColor()
{
	return &defaultCl;
}

void Colors::setDefaultColor(Color defaultCl)
{
	this->defaultCl = defaultCl;
}

/**
 * Coverts a color string in the from of (red, green, blue) to an int vector.
 * @param colorStr 
 *				The color string.
 * @return 
 *				The color as an int vector.
 */
Color Colors::convertStrToColor(string colorStr)
{
	string temp = colorStr;
	
	int	red = convertStrToColorChannel(temp, colorStr, '(', ',');
	int green = convertStrToColorChannel(temp, colorStr, ',', ',');
	int blue = convertStrToColorChannel(temp, colorStr, ',', ')');
	
	Color ret(red, green, blue);
	return ret;
}

/**
 * Converts a string into the value for a color channel.
 * @param str
 *				The string that is to be converted.
 * @param colorStr
 *				The original color string.
 * @param lCh
 *				The character to look for for the left index.
 * @param rCh
 *				The character to look for for the right index.
 * @return
 *				The value of the color channel.
 * @throws InvalidColorException
 *				If the right or left index character cannot be found.
 */
int Colors::convertStrToColorChannel(string &str, string &colorStr, char lCh, char rCh)
{
	int leftIndex = str.find(lCh);
	if(leftIndex == string::npos)
	{
		cerr << "Color is not in format of (red, green, blue): " << colorStr << endl;
		throw InvalidColorException;
	}
	str = str.substr(leftIndex + 1, str.length());

	int rightIndex = str.find(rCh);
	if(rightIndex == string::npos)
	{
		cerr << "Color is not in format of (red, green, blue): " << colorStr << endl;
		throw InvalidColorException;
	}

	string channel = str.substr(0, rightIndex);
	str = str.substr(rightIndex, str.length());
	return atoi(channel.c_str());
}
