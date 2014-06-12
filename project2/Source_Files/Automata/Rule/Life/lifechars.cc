#include <stdlib.h>
#include "lifechars.h"
#include "automatonparser.h"
#include <sstream>

using namespace std;

/**
 * Implementation lifechars.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets alive to 0.
 */
LifeChars::LifeChars()
	: Chars()
{
	aliveCh = 0;
}

/**
 * Takes in a string representation of life-like char
 * struct and sets the values of alive and default.
 * @param brianCharStruct 
 *				The string brian char struct.
 */
LifeChars::LifeChars(string lifeCharStruct)
{
	map<string, string> chars = AutomatonParser::parse(lifeCharStruct);
	aliveCh = atoi(AutomatonParser::getValue(chars, "Alive", true).c_str());
	setDefaultChar(atoi(AutomatonParser::getValue(chars, "Dead", true).c_str()));
}

/**
 * Constructs life-like chars with the given values.
 * @param aliveCh
 *				The alive character value.
 * @param defaultCh
 *				The default character value.
 */
LifeChars::LifeChars(int aliveCh, int defaultCh)
	: Chars(defaultCh)
{
	this->aliveCh = aliveCh;
}

/**
 * Copy constructor.
 * @param lifeChars 
 *				The life-like chars to be copied.
 */
LifeChars::LifeChars(const LifeChars &lifeChars)
	: Chars(lifeChars)
{
	aliveCh = lifeChars.aliveCh;
}

/**
 * Destructor
 */
LifeChars::~LifeChars() {}

/**
 * Overloaded assignment operator.
 * @param lifeChars 
 *				The life-like chars to be copied.
 * @return 
 *				A copy of the life-like chars.
 */
LifeChars& LifeChars::operator=(const LifeChars &lifeChars)
{
	if(this == &lifeChars) return *this;
	Chars::operator=(lifeChars);
	aliveCh = lifeChars.aliveCh;
	return *this;
}

/**
 * Gets the alive character value.
 * @return 
 *				The alive character value as an int.
 */
int LifeChars::getAliveChar()
{
	return aliveCh;
}

/**
 * Sets the alive character value.
 * @param readyCh 
 *				The value for the alive character to be set to.
 */
void LifeChars::setAliveChar(int aliveCh)
{
	this->aliveCh = aliveCh;
}

/**
 * Creates a string life-like chars struct in the form of Chars = { Alive = aliveCh; Dead = defaultCh };
 * @return 
 *				A string representation of life-like chars struct.
 */
string LifeChars::toString()
{
	ostringstream ret;
	ret << "Chars = {\n\t\tAlive = " << aliveCh << ";\n\t\tDead = " << getDefaultChar() << ";\n\t};";
	return ret.str();
}
