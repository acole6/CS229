#ifndef LIFEINITIAL_H
#define LIFEINITIAL_H

#include "initial.h"

/**
 * class that stores data for Life-like automaton initial
 * @author Alex Cole
 */
class LifeInitial : public Initial
{
public:
    /**
     * Default constructor that sets initial cells to 0.
     */
    LifeInitial();

    /**
     * Constructor that sets the initial cells to the given cells.
     * @param cells
     *              The given cells to assign the initial cells.
     */
    LifeInitial(vector<Cell> cells);

    /**
     * Constructor that takes in a like-like initial struct and terrain
     * to set the initial cells based on automaton terrain.
     * @param lifeInitialStruct
     *              The life-like initial struct string
     * @param terrain
     *              The life-like automaton terrain.
     */
    LifeInitial(string lifeInitialStruct, Range *terrain);

    /**
     * Copy constructor
     * @param lifeInitial
     *              The life-like initial to be copied.
     */
    LifeInitial(const LifeInitial &lifeInitial);

    /**
     * Destructor
     */
    virtual ~LifeInitial();

    /**
     * Overloaded assignment operator.
     * @param lifeInitial
     *              The life-like initial to be copied.
     * @return
     *              A copy of life-like initial.
     */
    LifeInitial& operator=(const LifeInitial &lifeInitial);

    /**
     * Creates a string life-like initial struct in the form of Initial = { Alive = cells; };
     * @return
     *              A string representation of life-like initial struct.
     */
    virtual string toString();
};

#endif
