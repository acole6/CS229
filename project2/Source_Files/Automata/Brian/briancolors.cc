#include "briancolors.h"
#include "automatonparser.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of briancolors.h
 * @author Alex Cole
 */

/**
 * Default constructor. Sets ready and firing to colors with all 0 values.
 */
BrianColors::BrianColors() {}

/**
 * Takes in a string representation of a brian colors struct
 * and sets the values of ready, firing and default
 * @param brianColorStruct
 *              The string brian colors struct
 */
BrianColors::BrianColors(string brianColorStruct)
{
    map<string, string> colors = AutomatonParser::parse(brianColorStruct);
    init(convertStrToColor(AutomatonParser::getValue(colors, "Ready", true)),
        convertStrToColor(AutomatonParser::getValue(colors, "Firing", true)),
        convertStrToColor(AutomatonParser::getValue(colors, "Refactory", true)));
}

/**
 * Constructs brian colors with the given colors
 * @param readyCl
 *              The ready RGB color.
 * @param firingCl
 *              The firing RGB color.
 * @param defaultCl
 *              The default RGB color.
 */
BrianColors::BrianColors(Color readyCl, Color firingCl, Color defaultCl)
{
    init(readyCl, firingCl, defaultCl);
}

/**
 * Copy constructor.
 * @param brianColors
 *              The brian colors to be copied.
 */
BrianColors::BrianColors(const BrianColors &brianColors)
    : Colors(brianColors)
{
    readyCl = brianColors.readyCl;
    firingCl = brianColors.firingCl;
}


/**
 * Destructor
 */
BrianColors::~BrianColors() {}

/**
 * Overloaded assignment operator.
 * @param brianColors
 *              The brian colors to be copied.
 * @return
 *              A copy of given brian colors.
 */
BrianColors& BrianColors::operator=(const BrianColors &brianColors)
{
    if(this == &brianColors) return *this;
    Colors::operator=(brianColors);
    readyCl = brianColors.readyCl;
    firingCl = brianColors.firingCl;
    return *this;
}

/**
 * Gets the ready color.
 * @return
 *              A pointer to the ready color.
 */
Color* BrianColors::getReadyColor()
{
    return &readyCl;
}

/**
 * Gets the firing color
 * @return
 *              A pointer to the firing color.
 */
Color* BrianColors::getFiringColor()
{
    return &firingCl;
}

/**
 * Creates a string brian colors struct in the form of Colors = { Ready = readyCl; Firing = firingCl; Refactory = defaultCl; };
 * @return
 *              A string representation of brian colors struct
 */
string BrianColors::toString()
{
    ostringstream ret;
    ret << "Colors = {\n\t\tReady = " << readyCl.toString() << ";\n\t\tFiring = " << firingCl.toString() << ";\n\t\tRefactory = " << getDefaultColor()->toString() << ";\n\t};";
    return ret.str();
}

/**
 * Initializes the colors to the given RGB colors
 * @param readyCl
 *              The ready RGB color.
 * @param firingCl
 *              The firing RGB color.
 * @param defaultCl
 *              The default RGB color.
 */
void BrianColors::init(Color readyCl, Color firingCl, Color defaultCl)
{
    this->readyCl = readyCl;
    this->firingCl = firingCl;
    setDefaultColor(defaultCl);
}
