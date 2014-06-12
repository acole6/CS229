#include <stdlib.h>
#include "elementarychars.h"
#include "automatonparser.h"
#include <iostream>
#include <sstream>

using namespace std;

/**
 * Implementation of elementarychars.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets one character to 0.
 */
ElementaryChars::ElementaryChars()
	: Chars()
{
	oneCh = 0;
}

/**
 * Takes in a string representation of elementary chars
 * struct and sets the values of one and default characters
 * @param elementaryCharStruct 
 *				The string elementary chars struct
 */
ElementaryChars::ElementaryChars(string elementaryCharStruct)
{
	map<string, string> chars = AutomatonParser::parse(elementaryCharStruct);
	oneCh = atoi(AutomatonParser::getValue(chars, "One", true).c_str());
	setDefaultChar(atoi(AutomatonParser::getValue(chars, "Zero", true).c_str()));
}

/**
 * Constructs elementary chars with the given values.
 * @param oneCh
 *				The one character value.
 * @param defaultCh
 *				The default character value.
 */
ElementaryChars::ElementaryChars(int oneCh, int defaultCh)
	: Chars(defaultCh)
{
	this->oneCh = oneCh;
}

/**
 * Copy constructor.
 * @param elementaryChars 
 *				The elementary chars to be copied.
 */
ElementaryChars::ElementaryChars(const ElementaryChars &elementaryChars)
	: Chars(elementaryChars)
{
	oneCh = elementaryChars.oneCh;
}

/**
 * Destructor
 */
ElementaryChars::~ElementaryChars() {}

/**
 * Overloaded assignment operator.
 * @param elementaryChars 
 *				The elementary chars to be copied.
 * @return 
 *				A copy of the elementary chars.
 */
ElementaryChars& ElementaryChars::operator=(const ElementaryChars &elementaryChars)
{
	if(this == &elementaryChars) return *this;
	Chars::operator=(elementaryChars);
	oneCh = elementaryChars.oneCh;
	return *this;
}

/**
 * Gets the one character value.
 * @return 
 *				The one character value as an int.
 */
int ElementaryChars::getOneChar()
{
	return oneCh;
}

/**
 * Sets the one character value.
 * @param oneCh
 *				The value for the one character to be set to.
 */
void ElementaryChars::setOneChar(int oneCh)
{
	this->oneCh = oneCh;
}

/**
 * Creates a string chars struct in the form of Chars = { One = oneCh; Zero = defaultCh; };
 * @return 
 *			A string representation of elementary chars struct.
 */
string ElementaryChars::toString()
{
	ostringstream ret;
	ret << "Chars = {\n\t\tOne = " << oneCh << ";\n\t\tZero = " << getDefaultChar() << ";\n\t};";
	return ret.str();
}
