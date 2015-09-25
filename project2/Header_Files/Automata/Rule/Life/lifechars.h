#ifndef LIFECHARS_H
#define LIFECHARS_H

#include "chars.h"

/**
 * class that stores data for Life-like automaton chars
 * @author Alex Cole
 */
class LifeChars : public Chars
{
    /**
     * alive character
     */
    int aliveCh;

public:
    /**
     * Default constructor that sets alive to 0.
     */
    LifeChars();

    /**
     * Takes in a string representation of life-like char
     * struct and sets the values of alive and default.
     * @param brianCharStruct
     *              The string brian char struct.
     */
    LifeChars(string lifeCharStruct);

    /**
     * Constructs life-like chars with the given values.
     * @param aliveCh
     *              The alive character value.
     * @param defaultCh
     *              The default character value.
     */
    LifeChars(int aliveCh, int defaultCh);

    /**
     * Copy constructor.
     * @param lifeChars
     *              The life-like chars to be copied.
     */
    LifeChars(const LifeChars &lifeChars);

    /**
     * Destructor
     */
    virtual ~LifeChars();

    /**
     * Overloaded assignment operator.
     * @param lifeChars
     *              The life-like chars to be copied.
     * @return
     *              A copy of the life-like chars.
     */
    LifeChars& operator=(const LifeChars &lifeChars);

    /**
     * Gets the alive character value.
     * @return
     *              The alive character value as an int.
     */
    int getAliveChar();

    /**
     * Sets the alive character value.
     * @param readyCh
     *              The value for the alive character to be set to.
     */
    void setAliveChar(int aliveCh);

    /**
     * Creates a string life-like chars struct in the form of Chars = { Alive = aliveCh; Dead = defaultCh };
     * @return
     *              A string representation of life-like chars struct.
     */
    virtual string toString();
};

#endif
