#include "lifecolors.h"
#include "automatonparser.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>

/**
 * Implementation lifecolors.h
 * @author Alex Cole
 */

/**
 * Default constructor. Sets alive to color with all 0 values.
 */
LifeColors::LifeColors() {}

/**
 * Takes in a string representation of a like-like colors struct
 * and sets the values of alive and default
 * @param brianColorStruct 
 *				The string brian colors struct
 */
LifeColors::LifeColors(string lifeColorStruct)
{
	map<string, string> colors = AutomatonParser::parse(lifeColorStruct);
	init(convertStrToColor(AutomatonParser::getValue(colors, "Alive", true)), convertStrToColor(AutomatonParser::getValue(colors, "Dead", true)));
}

/**
 * Constructs like-like colors with the given colors
 * @param aliveCl 
 *				The ready RGB color.
 * @param defaultCl
 *				The default RGB color.
 */
LifeColors::LifeColors(Color aliveCl, Color defaultCl)
{
	init(aliveCl, defaultCl);
}

/**
 * Copy constructor.
 * @param lifeColors 
 *				The life-like colors to be copied.
 */
LifeColors::LifeColors(const LifeColors &lifeColors)
	: Colors(lifeColors)
{
	aliveCl = lifeColors.aliveCl;
}

/**
 * Destructor
 */
LifeColors::~LifeColors() {}

/**
 * Overloaded assignment operator.
 * @param lifeColors 
 *				The life-like colors to be copied.
 * @return 
 *				A copy of given life-like colors.
 */
LifeColors& LifeColors::operator=(const LifeColors &lifeColors)
{
	if(this == &lifeColors) return *this;
	Colors::operator=(lifeColors);
	aliveCl = lifeColors.aliveCl;
	return *this;
}

/**
 * Gets the alive color.
 * @return 
 *				A pointer to the alive color.
 */
Color* LifeColors::getAliveColor()
{
	return &aliveCl;
}

/**
 * Creates a string life-like colors struct in the form of Colors = { Alive = aliveCl; Dead = defaultCl; };
 * @return 
 *				A string representation of life-like colors struct.
 */
string LifeColors::toString()
{
	ostringstream ret;
	ret << "Colors = {\n\t\tAlive = " << aliveCl.toString() << ";\n\t\tDead = " << getDefaultColor()->toString() << ";\n\t};";
	return ret.str();
}

/**
 * Initializes the life-like colors to the given RGB colors
 * @param aliveCl 
 *				The ready RGB color. 
 * @param defaultCl
 *				The default RGB color.
 */
void LifeColors::init(Color aliveCl, Color defaultCl)
{
	this->aliveCl = aliveCl;
	setDefaultColor(defaultCl);
}
