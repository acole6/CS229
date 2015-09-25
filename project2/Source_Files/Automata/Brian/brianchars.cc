#include <stdlib.h>
#include "brianchars.h"
#include "automatonparser.h"
#include <iostream>
#include <sstream>

using namespace std;

/**
 * Implementation of brianchars.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets ready and firing
 * to 0;
 */
BrianChars::BrianChars()
    : Chars()
{
    readyCh = 0;
    firingCh = 0;
}

/**
 * Takes in a string representation of brian char
 * struct and sets the values of alive ready, firing
 * and default.
 * @param brianCharStruct
 *              The string brian char struct.
 */
BrianChars::BrianChars(string brianCharStruct)
{
    map<string, string> chars = AutomatonParser::parse(brianCharStruct);
    readyCh = atoi(AutomatonParser::getValue(chars, "Ready", true).c_str());
    firingCh = atoi(AutomatonParser::getValue(chars, "Firing", true).c_str());
    setDefaultChar(atoi(AutomatonParser::getValue(chars, "Refactory", true).c_str()));
}

/**
 * Constructs brian chars with the given values.
 * @param readyCh
 *              The ready character value.
 * @param firingCh
 *              The firing character value.
 * @param defaultCh
 *              The default character value.
 */
BrianChars::BrianChars(int readyCh, int firingCh, int defaultCh)
    : Chars(defaultCh)
{
    this->readyCh = readyCh;
    this->firingCh = firingCh;
}

/**
 * Copy constructor.
 * @param brianChars
 *              The brian chars to be copied.
 */
BrianChars::BrianChars(const BrianChars &brianChars)
    : Chars(brianChars)
{
    readyCh = brianChars.readyCh;
    firingCh = brianChars.firingCh;
}

/**
 * Destructor
 */
BrianChars::~BrianChars() {}

/**
 * Overloaded assignment operator.
 * @param brianChars
 *              The brian chars to be copied.
 * @return
 *              A copy of the brian chars.
 */
BrianChars& BrianChars::operator=(const BrianChars &brianChars)
{
    if(this == &brianChars) return *this;
    Chars::operator=(brianChars);
    readyCh = brianChars.readyCh;
    firingCh = brianChars.firingCh;
    return *this;
}

/**
 * Gets the ready character value.
 * @return
 *              The ready character value as an int.
 */
int BrianChars::getReadyChar()
{
    return readyCh;
}

/**
 * Gets the firing character value.
 * @return
 *              The firing character value as an int.
 */
int BrianChars::getFiringChar()
{
    return firingCh;
}

/**
 * Sets the ready character value.
 * @param readyCh
 *              The value for the ready character to be set to.
 */
void BrianChars::setReadyChar(int readyCh)
{
    this->readyCh = readyCh;
}

/**
 * Sets the firing character value.
 * @param readyCh
 *              The value for the firing character to be set to.
 */
void BrianChars::setFiringChar(int firingCh)
{
    this->firingCh = firingCh;
}

/**
 * Creates a string brian chars struct in the form of Chars = { Ready = readyCh; Firing = firingCh; Refactory = defaultCh };
 * @return
 *              A string representation of brian chars struct.
 */
string BrianChars::toString()
{
    ostringstream ret;
    ret << "Chars = {\n\t\tReady = " << readyCh << ";\n\t\tFiring = " << firingCh << ";\n\t\tRefactory = " << getDefaultChar() << ";\n\t};";
    return ret.str();
}
