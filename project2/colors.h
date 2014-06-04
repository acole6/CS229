#ifndef COLORS_H
#define COLORS_H

#include "color.h"

/**
 * abstract class that stores data from colors struct
 * @author Alex Cole
 */
class Colors
{
protected:
	/**
	 * RGB default color
	 */
	Color defaultCl;

public:
	/**
	 * Default constructor. Sets the default
	 * color with all 0 values.
	 */
	Colors();

	/**
	 * Constructs with a string representation of a colors struct.
	 * @param colorsStruct 
	 *				The string colors struct.
	 */
	Colors(string colorsStruct);

	/**
	 * Constructs with given default color value.
	 * @param defalutCl 
	 *				The default color.
	 */
	Colors(Color defaultCl);

	/**
	 * Copy constructor.
	 * @param colors 
	 *				The colors to be copied.
	 */
	Colors(const Colors &colors);

	/**
	 * Destructor
	 */
	virtual ~Colors();

	/**
	 * Overloaded assignment operator.
	 * @param colors 
	 *				The colors to be copied.
	 * @return 
	 *				A copy of given colors.
	 */
	Colors& operator=(const Colors &colors);

	/**
	 * Gets the default color.
	 * @return 
	 *				A pointer to default color.
	 */
	Color* getDefaultColor();

	/**
	 * Not implemented.
	 * Creates a string colors struct in the form of Colors = { Default = defaultCl; };
	 * @return 
	 *				A string representation of colors struct.
	 */
	virtual string toString() = 0;

protected:
	/**
	 * Coverts a color string in the from of (red, green, blue) to an int vector.
	 * @param colorStr 
	 *				The color string.
	 * @return 
	 *				The color as an int vector.
	 */
	Color convertStrToColor(string colorStr);

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
	int convertStrToColorChannel(string &str, string &colorStr, char lCh, char rCh);
};

#endif
