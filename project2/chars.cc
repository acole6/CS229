#include <stdlib.h>
#include "chars.h"
#include <iostream>
#include <sstream>

using namespace std;

/**
 * Implementation of chars.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets default 
 * character to 0.
 */
Chars::Chars()
{
	defaultCh = 0;
}

/**
 * Constructs Chars with the given value.
 * @param defaultCh 
 *			The default character value
 */
Chars::Chars(int defaultCh)
{
	this->defaultCh = defaultCh;
}

/**
 * Copy constructor.
 * @param chars 
 *			The chars to be copied.
 */
Chars::Chars(const Chars &chars)
{
	defaultCh = chars.defaultCh;
}

/**
 * Destructor
 */
Chars::~Chars() {}

/**
 * Overloaded assignment operator.
 * @param chars 
 *			The chars to be copied.
 * @return 
 *			A copy of the given chars.
 */
Chars& Chars::operator=(const Chars &chars)
{
	if(this == &chars) return *this;
	defaultCh = chars.defaultCh;
	return *this;
}

/**
 * Gets the default character value.
 * @return 
 *			The default character value as an int.
 */
int Chars::getDefaultChar()
{
	return defaultCh;
}

/**
 * Sets the default character value.
 * @param defaultCh 
 *			The value for the default character to be set to.
 */
void Chars::setDefaultChar(int defaultCh)
{
	this->defaultCh = defaultCh;
}
