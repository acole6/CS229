#ifndef ELEMENTARY_H
#define ELEMENTARY_H

#include "ruleautomaton.h"

/**
 * class that represents an Elementary cellular automaton
 * @author Alex Cole
 */
class Elementary : public RuleAutomaton
{	
public:
	/**
	 * Default constructor that sets values
	 * to NULL and the name and rule to an empty string.
	 */
	Elementary();

	/**
	 * Takes in a string elementary struct and sets the values to
	 * the values in the struct.
	 * @param elementaryStruct 
	 *					The string elementary struct
	 * @throws InvalidRuleException
	 *					If rule is not in the range 0-255 (inclusive).
	 */
	Elementary(string elemetnaryStruct);

	/**
	 * Copy constructor.
	 * @param elementary 
	 *					The elementary automaton to be copied.
	 */
	Elementary(const Elementary &elementary);

	/**
	 * Destructor
	 */
	virtual ~Elementary();

	/**
	 * Overloaded assignment operator.
	 * @param elementary 
	 *					The elementary automaton to be copied.
	 * @return 
	 *					A copy of the elementary automaton.
	 */
	Elementary& operator=(const Elementary &elementary);

	/**
	 * Determines the next state of a given cell based on the world
	 * and neighboring cells.
	 * @param world
	 *				The grid of cells.
	 * @param cell
	 *				The cell that the next state needs to be determined.
	 * @return
	 *				The next state of the cell.
	 */
	virtual State nextCellState(vector<vector<Cell>> &world, Cell &cell);
	
	/**
	 * Gets the char representation of the state of the given cell.
	 * @param cell
	 *				The cell to get the char value of.
	 * @return
	 *				The char representation of the state of the cell.
	 */
	virtual char getChar(Cell &cell);

	/**
	 * Gets the color representation of the state of the given cell.
	 * @param cell
	 *				The cell to get the color value of.
	 * @return
	 *				The color representation of the state of the cell.
	 */
	virtual Color getColor(Cell &cell);

	/**
	 * Creates a string in the automaton file format.
	 * @return 
	 *				String representation of automaton file
	 */
	virtual string toString();

private:
	/**
	 * Gets the bit value in an unsigned char at the given position.
	 * @param ch
	 *				The character to get a bit at a specific position.
	 * @param pos
	 *				The position of the bit to get.
	 * @return
	 *				The value of the bit (1 or 0) as an int.
	 */
	int getBit(unsigned char ch, int pos);

	/**
	 * Creates a string rule pattern based on the state of the 3 cells
	 * above the given cell (accounts for wrap around).
	 * @param world
	 *				The grid of cells to compare the cell to its neighbors.
	 * @param cell
	 *				The cell used to determine the rule pattern.
	 * @return
	 *				A string representation of the 3 cells' states above the given cell.
	 */
	string rulePattern(vector<vector<Cell>> &world, Cell &cell);

	/**
	 * Checks to see if the rule is a valid rule in the range 0-255 (inclusive).
	 * @return
	 *				True if valid otherwise false.
	 */
	bool validRule();
};

#endif
