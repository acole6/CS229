#ifndef INITIAL_H
#define INITIAL_H

#include "cell.h"
#include "range.h"
#include <vector>

const int InvalidInitialValueException = 9;

/**
 * abstract class that stores the initial struct
 * @author Alex Cole
 */
class Initial
{
private:
	/**
	 * initial cells of the automaton
	 */
	vector<Cell> cells;

public:
	/**
	 * Default constructor that sets number of initial cells to 0.
	 */
	Initial();

	/**
	 * Constructor that sets initial cells to the given cells.
	 * @param cells
	 *				The cells to set the initial cells to.
	 */
	Initial(vector<Cell> cells);

	/**
	 * Destructor
	 */
	virtual ~Initial();

	/**
	 * Copy constructor.
	 * @param initial
	 *				The initial to be copied.
	 */
	Initial(const Initial &initial);

	/**
	 * Overloaded operator assignment.
	 * @param initial
	 *				The initial to be copied.
	 * @return
	 *				A copy of the given initial.
	 */
	Initial& operator=(const Initial &initial);

	/**
	 * Gets the cells.
	 * @return 
	 *			A cell vector of initial cells.
	 */
	vector<Cell> getCells() const;

	/**
	 * Adds a cell to the vector of cells (does not check for duplicates).
	 * @param cell 
	 *				The cell to be added.
	 */
	void addCell(Cell cell);

	/**
	 * Empties the cell vector of initial cells.
	 */
	void clearCells();

	/**
	 * Gets the number of cells in the initial cell vector.
	 * @return
	 *				The number of cells.
	 */
	int size();

	/**
	 * Checks to see if a cell is in the vector of cells with the
	 * given x and y values.
	 * @param x 
	 *				The x value.
	 * @param y 
	 *				The y value.
	 * @return 
	 *				True if the cell is in the vector otherwise false.
	 */
	bool contains(int x, int y);

	/**
	 * Not implemented.
	 * Creates a string initial struct in the form of Initial = { Identifier = cells; };
	 * @return 
	 *				String representation of initial struct.
	 */
	virtual string toString() = 0;

	/**
	 * Initializes the initial object with a given terrain range and string of cells in the form of (cell, cell, cell,...).
	 * @param initialCells 
	 *				The string of cells.
	 * @param terrain 
	 *				The automaton terrain.
	 * @param state 
	 *				The state to set the cells to.
	 * @throws InvalidInitialValueException
	 *				If there is a comma missing between cells.
	 */
	void convertCellStr(string initalCells, Range *terrain, State state);

	/**
	 * Converts cells given from a world grid to cells in the automaton terrain.
	 * @param worldCells
	 *				The cells from the world grid to be converted.
	 * @param terrain
	 *				The automaton terrain.
	 */
	void convertToTerrainCells(vector<Cell> worldCells, Range *terrain);

private:
	/**
	 * Wraps a cell that is outside of the terrain to fit it into the terrain.
	 * @param pos 
	 *				The position in the range.
	 * @param start 
	 *				The start value of the range.
	 * @param end 
	 *				The end value of the range.
	 * @return 
	 *				The value of position after it has been wrapped around to be in the terrain.
	 */
	int fitToTerrain(int pos, int start, int end);

	/**
	 * Gets a cell string in the form of x,y from a string of cells.
	 * @param initialCells
	 *				The string of cells.
	 * @return
	 *				A string representation of a cell.
	 * @throws InvalidInitialValueException
	 *				If the cell is missing the left bracket '(' or the right bracket ')'
	 */
	string extractCellStr(string &initialCells);

	/**
	 * Add cell from a cell string to the initial cells if it is not already in the initial cells.
	 * @param cellStr
	 *				The cell string.
	 * @param terrain
	 *				The automaton terrain.
	 * @param state
	 *				The state to set the cell to.
	 * @thorws InvlaidInitialValueException
	 *				If the cell string is missing a comma between x and y values.
	 */
	void addCellFromCellStr(string &cellStr, Range *terrain, State state);
};

#endif
