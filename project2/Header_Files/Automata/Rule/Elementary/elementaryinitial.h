#ifndef ELEMENTARYINITIAL_H
#define ELEMENTARYINITIAL_H

#include "initial.h"

/**
 * class that stores data for Elementary automaton initial
 * @author Alex Cole
 */
class ElementaryInitial : public Initial
{
public:
    /**
     * Default constructor that sets initial cells to 0.
     */
    ElementaryInitial();

    /**
     * Constructor that sets the initial cells to the given cells.
     * @param cells
     *              The given cells to assign the initial cells.
     */
    ElementaryInitial(vector<Cell> cells);

    /**
     * Constructor that takes in a elementary initial strcut and terrain
     * to set the initial cells based on automaton terrain.
     * @param elementaryInitialStruct
     *              The elementary initial struct string
     * @param terrain
     *              The elementary automaton terrain.
     */
    ElementaryInitial(string elementaryInitialStruct, Range *terrain);


    /**
     * Copy constructor
     * @param elementaryInitial
     *              The elementary initial to be copied.
     */
    ElementaryInitial(const ElementaryInitial &elementaryInitial);

    /**
     * Destructor
     */
    virtual ~ElementaryInitial();

    /**
     * Overloaded assignment operator.
     * @param elementaryInitial
     *              The elementary initial to be copied.
     * @return
     *              A copy of elementary initial.
     */
    ElementaryInitial& operator=(const ElementaryInitial &elementaryInitial);

    /**
     * Creates a string elementary initial struct in the form of Initial = { One = cells; };
     * @return
     *              A string representation of elementary initial struct.
     */
    virtual string toString();
};

#endif
