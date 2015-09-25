#include "color.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of color.h
 * @author Alex Cole
 */

/**
 * Default construct sets all channels to 0.
 */
Color::Color()
{
    color = vector<int>(size, 0);
}

/**
 * Sets initial channels to the given red, green and
 * blue values.
 * @param red
 *          The red value.
 * @param green
 *          The green value.
 * @param blue
 *          The blue value.
 */
Color::Color(int red, int green, int blue)
{
    if(!color.empty()) color.clear();
    checkChannelRange(red, "Red");
    checkChannelRange(green, "Green");
    checkChannelRange(blue, "Blue");
    color.push_back(red);
    color.push_back(green);
    color.push_back(blue);
}

/**
 * Copy constructor.
 * @param color
 *          The color to be copied.
 */
Color::Color(const Color &color)
{
    this->color = color.color;
}

/**
 * Destructor
 */
Color::~Color() {}

/**
 * Overloaded assignment operator.
 * @param color
 *          The color to be copied
 * @return
 *          A copy of the given color.
 */
Color& Color::operator=(const Color &color)
{
    if(this == &color) return *this;
    this->color = color.color;
    return *this;
}

/**
 * Gets RGB vector
 * @return
 *          The color as a int vector.
 */
vector<int> Color::getColor()
{
    return color;
}

/**
 * Sets the color to the given color if
 * the given color is of size 3.
 * @param color
 *          The int vector to set the color to.
 */
void Color::setColor(vector<int> color)
{
    if(color.size() == (unsigned) size) this->color = color;
}

/**
 * Gets the value of the red channel.
 * @return
 *      the value of the red channel.
 */
int Color::getRed()
{
    return color[0];
}

/**
 * Gets the value of the green channel.
 * @return
 *      the value of the green channel.
 */
int Color::getGreen()
{
    return color[1];
}

/**
 * Gets the value of the blue channel.
 * @return
 *      the value of the blue channel.
 */
int Color::getBlue()
{
    return color[2];
}

/**
 * Sets the red channel to the given value
 * @param red
 *          The value to set the channel to
 */
void Color::setRed(int red)
{
    checkChannelRange(red, "Red");
    color[0] = red;
}

/**
 * Sets the green channel to the given value
 * @param green
 *          The value to set the channel to
 */
void Color::setGreen(int green)
{
    checkChannelRange(green, "Green");
    color[1] = green;
}

/**
 * Sets the blue channel to the given value
 * @param blue
 *          The value to set the channel to
 */
void Color::setBlue(int blue)
{
    checkChannelRange(blue, "Blue");
    color[2] = blue;
}

/**
 * Color in the form of (red, green, blue).
 * @return
 *          String representation of color.
 */
string Color::toString()
{
    ostringstream ret;
    ret << "(";
    unsigned int length = color.size();
    for(unsigned int i = 0; i < length; i++)
    {
        if(i == (length - 1))
        {
            ret << color[i];
        }
        else
        {
            ret << color[i] << ", ";
        }
    }
    ret << ")";
    return ret.str();
}

/**
 * Checks to see if the given value is within the range of 0-255 (inclusive).
 * @param value
 *          The value to be checked.
 * @param channel
 *          The name of the color channel.
 * @throws InvalidColorException
 *          If the value is not within the range of 0-255 (inclusive).
 */
void Color::checkChannelRange(int value, string channel)
{
    if(value < 0 || value > 255)
    {
        cerr << "Invalid color channel value, " << value << ", for " << channel << "channel.\n";
        throw InvalidColorException;
    }
}
