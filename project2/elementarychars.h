#ifndef ELEMENTARYCHARS_H
#define ELEMENTARYCHARS_H

#include "chars.h"

/**
 * class that stores data for Elementary automaton chars
 * @author Alex Cole
 */
class ElementaryChars : public Chars
{
	/**
	 * one character
	 */
	int oneCh;

public:
	/**
	 * Default constructor that sets one character to 0.
	 */
	ElementaryChars();

	/**
	 * Takes in a string representation of elementary chars
	 * struct and sets the values of one and default characters
	 * @param elementaryCharStruct 
	 *				The string elementary chars struct
	 */
	ElementaryChars(string elementaryCharStruct);

	/**
	 * Constructs elementary chars with the given values.
	 * @param oneCh
	 *				The one character value.
	 * @param defaultCh
	 *				The default character value.
	 */
	ElementaryChars(int oneCh, int defaultCh);

	/**
	 * Copy constructor.
	 * @param elementaryChars 
	 *				The elementary chars to be copied.
	 */
	ElementaryChars(const ElementaryChars &elementaryChars);

	/**
	 * Destructor
	 */
	virtual ~ElementaryChars();

	/**
	 * Overloaded assignment operator.
	 * @param elementaryChars 
	 *				The elementary chars to be copied.
	 * @return 
	 *				A copy of the elementary chars.
	 */
	ElementaryChars& operator=(const ElementaryChars &elementaryChars);

	/**
	 * Gets the one character value.
	 * @return 
	 *				The one character value as an int.
	 */
	int getOneChar();

	/**
	 * Sets the one character value.
	 * @param oneCh
	 *				The value for the one character to be set to.
	 */
	void setOneChar(int oneCh);

	/**
	 * Creates a string chars struct in the form of Chars = { One = oneCh; Zero = defaultCh; };
	 * @return 
	 *			A string representation of elementary chars struct.
	 */
	virtual string toString();
};

#endif
