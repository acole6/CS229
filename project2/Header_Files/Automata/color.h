#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <vector>

using namespace std;

const int InvalidColorException = 8;

/**
 * class that represents a color by storing it
 * in a vector. 0 - red, 1 - green, 2 - blue
 * @author Alex Cole
 */
class Color
{
	/**
	 * 3 color channels for RGB
	 */
	static const int size = 3;

	/**
	 * vector to store color channels
	 */
	vector<int> color;

public:
	/**
	 * Default construct sets all channels to 0.
	 */
	Color();

	/**
	 * Sets initial channels to the given red, green and
	 * blue values.
	 * @param red 
	 *			The red value.
	 * @param green 
	 *			The green value.
	 * @param blue 
	 *			The blue value.
	 */
	Color(int red, int green, int blue);

	/**
	 * Copy constructor.
	 * @param color 
	 *			The color to be copied.
	 */
	Color(const Color &color);

	/**
	 * Destructor
	 */
	~Color();

	/**
	 * Overloaded assignment operator.
	 * @param color 
	 *			The color to be copied
	 * @return 
	 *			A copy of the given color.
	 */
	Color& operator=(const Color &color);

	/**
	 * Gets RGB vector
	 * @return 
	 *			The color as a int vector.
	 */
	vector<int> getColor();

	/**
	 * Sets the color to the given color if
	 * the given color is of size 3.
	 * @param color
	 *			The int vector to set the color to.
	 */
	void setColor(vector<int> color);

	/**
	 * Gets the value of the red channel.
	 * @return
	 *		the value of the red channel.
	 */
	int getRed();

	/**
	 * Gets the value of the green channel.
	 * @return
	 *		the value of the green channel.
	 */
	int getGreen();

	/**
	 * Gets the value of the blue channel.
	 * @return
	 *		the value of the blue channel.
	 */
	int getBlue();

	/**
	 * Sets the red channel to the given value
	 * @param red
	 *			The value to set the channel to
	 */
	void setRed(int red);

	/**
	 * Sets the green channel to the given value
	 * @param green
	 *			The value to set the channel to
	 */
	void setGreen(int green);

	/**
	 * Sets the blue channel to the given value
	 * @param blue
	 *			The value to set the channel to
	 */
	void setBlue(int blue);

	/**
	 * Color in the form of (red, green, blue).
	 * @return 
	 *			String representation of color.
	 */
	string toString();

private:
	/**
	 * Checks to see if the given value is within the range of 0-255 (inclusive).
	 * @param value
	 *			The value to be checked.
	 * @param channel
	 *			The name of the color channel.
	 * @throws InvalidColorException
	 *			If the value is not within the range of 0-255 (inclusive).
	 */
	void checkChannelRange(int value, string channel);
};

#endif
