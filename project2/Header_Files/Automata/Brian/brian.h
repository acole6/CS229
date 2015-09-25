#ifndef BRIAN_H
#define BRIAN_H

#include "cellularautomaton.h"

/**
 * class that represents Brian's Brain cellular automaton
 * @author Alex Cole
 */
class Brian : public CellularAutomaton
{
public:
    /**
    * Default constructor that sets values
    * to NULL and the name to an empty string.
    */
    Brian();

    /**
    * Takes in a string brian automaton struct and sets the values to
    * the values in the struct
    * @param brianStruct
    *               The string brian automaton struct
    */
    Brian(string brianStruct);

    /**
     * Copy constructor.
     * @param brian
     *              The brian automaton to be copied.
     */
    Brian(const Brian &brian);

    /**
     * Destructor
     */
    virtual ~Brian();

    /**
     * Overloaded assignment operator.
     * @param brian
     *               The brian automaton to be copied.
     * @return
     *              A copy of the brian automaton.
     */
    Brian& operator=(const Brian &brian);

    /**
     * Determines the next state of a given cell based on the world
     * and neighboring cells.
     * @param world
     *              The grid of cells.
     * @param cell
     *              The cell that the next state needs to be determined.
     * @return
     *              The next state of the cell.
     */
    virtual State nextCellState(vector<vector<Cell>> &world, Cell &cell);

    /**
     * Gets the char representation of the state of the given cell.
     * @param cell
     *              The cell to get the char value of.
     * @return
     *              The char representation of the state of the cell.
     */
    virtual char getChar(Cell &cell);

    /**
     * Gets the color representation of the state of the given cell.
     * @param cell
     *              The cell to get the color value of.
     * @return
     *              The color representation of the state of the cell.
     */
    virtual Color getColor(Cell &cell);

    /**
     * Creates a string in the automaton file format.
     * @return
     *              String representation of automaton file
     */
    virtual string toString();
};

#endif
