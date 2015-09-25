#ifndef BRIANINITIAL_H
#define BRIANINITIAL_H

#include "initial.h"

/**
 * class that stores data for Brian's Brain automaton initial
 * @author Alex Cole
 */
class BrianInitial : public Initial
{
public:
    /**
     * Default constructor that sets initial cells to 0.
     */
    BrianInitial();

    /**
     * Constructor that sets the initial cells to the given cells.
     * @param cells
     *              The given cells to assign the initial cells.
     */
    BrianInitial(vector<Cell> cells);

    /**
     * Constructor that takes in a brian initial strcut and terrain
     * to set the initial cells based on automaton terrain.
     * @param brianInitialStruct
     *              The brian initial struct string
     * @param terrain
     *              The brian automaton terrain.
     */
    BrianInitial(string brianInitialStruct, Range *terrain);

    /**
     * Copy constructor
     * @param brianInitial
     *              The brian initial to be copied.
     */
    BrianInitial(const BrianInitial &brianInitial);

    /**
     * Destructor
     */
    virtual ~BrianInitial();

    /**
     * Overloaded assignment operator.
     * @param brianInitial
     *              The brian initial to be copied.
     * @return
     *              A copy of brian initial.
     */
    BrianInitial& operator=(const BrianInitial &brianInitial);

    /**
     * Creates a string brian initial struct in the form of Initial = { Ready = readyCells; Firing = firingCells; };
     * @return
     *              A string representation of brian initial struct.
     */
    virtual string toString();
};

#endif
