#include "elementarycolors.h"
#include "automatonparser.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of elementarycolors.h
 * @author Alex Cole
 */

/**
 * Default constructor. Sets the one color
 * with all 0 values.
 */
ElementaryColors::ElementaryColors() {}

/**
 * Constructs with a string representation of
 * an elementary colors struct.
 * @param elementaryColorStruct
 *              The string elementary colors struct.
 */
ElementaryColors::ElementaryColors(string elementaryColorStruct)
{
    map<string, string> colors = AutomatonParser::parse(elementaryColorStruct);
    init(convertStrToColor(AutomatonParser::getValue(colors, "One", true)), convertStrToColor(AutomatonParser::getValue(colors, "Zero", true)));
}

/**
 * Constructs with given color values.
 * @param oneCl
 *              The one color.
 * @param defaultCl
 *              The default color.
 */
ElementaryColors::ElementaryColors(Color oneCl, Color defaultCl)
{
    init(oneCl, defaultCl);
}

/**
 * Copy constructor.
 * @param elementaryColors
 *              The elementary automaton colors to be copied.
 */
ElementaryColors::ElementaryColors(const ElementaryColors &elementaryColors)
    : Colors(elementaryColors)
{
    oneCl = elementaryColors.oneCl;
}

/**
 * Destructor
 */
ElementaryColors::~ElementaryColors() {}

/**
 * Overloaded assignment operator.
 * @param elementaryColors
 *              The elementary automaton colors to be copied
 * @return
 *              A copy of elementary automaton colors.
 */
ElementaryColors& ElementaryColors::operator=(const ElementaryColors &elementaryColors)
{
    if(this == &elementaryColors) return *this;
    Colors::operator=(elementaryColors);
    oneCl = elementaryColors.oneCl;
    return *this;
}

/**
 * Gets the one color.
 * @return
 *              A pointer to one color.
 */
Color* ElementaryColors::getOneColor()
{
    return &oneCl;
}

/**
 * Creates a string colors struct in the form of Colors = { One = oneCl; Zero = defaultCl; };
 * @return
 *              A string representation of elementary colors struct.
 */
string ElementaryColors::toString()
{
    ostringstream ret;
    ret << "Colors = {\n\t\tOne = " << oneCl.toString() << ";\n\t\tZero = " << getDefaultColor()->toString() << ";\n\t};";
    return ret.str();
}

/**
 * Initializes the elementary colors to the given RGB colors
 * @param oneCl
 *              The one RGB color.
 * @param defaultCl
 *              The default RGB color.
 */
void ElementaryColors::init(Color oneCl, Color defaultCl)
{
    this->oneCl = oneCl;
    setDefaultColor(defaultCl);
}
