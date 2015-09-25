#ifndef BRIANCHARS_H
#define BRIANCHARS_H

#include "chars.h"

/**
 * class that stores data for Brian's Brain automaton chars
 * @author Alex Cole
 */
class BrianChars : public Chars
{
    /**
     * ready character
     */
    int readyCh;

    /**
     * firing character
     */
    int firingCh;

public:
    /**
     * Default constructor that sets ready and firing
     * to 0.
     */
    BrianChars();

    /**
     * Takes in a string representation of brian char
     * struct and sets the values of ready, firing
     * and default.
     * @param brianCharStruct
     *              The string brian char struct.
     */
    BrianChars(string brianCharStruct);

    /**
     * Constructs brian chars with the given values.
     * @param readyCh
     *              The ready character value.
     * @param firingCh
     *              The firing character value.
     * @param defaultCh
     *              The default character value.
     */
    BrianChars(int readyCh, int firingCh, int defaultCh);

    /**
     * Copy constructor.
     * @param brianChars
     *              The brian chars to be copied.
     */
    BrianChars(const BrianChars &brianChars);

    /**
     * Destructor
     */
    virtual ~BrianChars();

    /**
     * Overloaded assignment operator.
     * @param brianChars
     *              The brian chars to be copied.
     * @return
     *              A copy of the brian chars.
     */
    BrianChars& operator=(const BrianChars &brianChars);

    /**
     * Gets the ready character value.
     * @return
     *              The ready character value as an int.
     */
    int getReadyChar();

    /**
     * Gets the firing character value.
     * @return
     *              The firing character value as an int.
     */
    int getFiringChar();

    /**
     * Sets the ready character value.
     * @param readyCh
     *              The value for the ready character to be set to.
     */
    void setReadyChar(int readyCh);

    /**
     * Sets the firing character value.
     * @param readyCh
     *              The value for the firing character to be set to.
     */
    void setFiringChar(int firingCh);

    /**
     * Creates a string brian chars struct in the form of Chars = { Ready = readyCh; Firing = firingCh; Refactory = defaultCh };
     * @return
     *              A string representation of brian chars struct.
     */
    virtual string toString();
};

#endif
