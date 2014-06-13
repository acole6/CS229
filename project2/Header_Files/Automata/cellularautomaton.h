#ifndef CELLULARAUTOMATON_H
#define CELLULARAUTOMATON_H

#include "range.h"
#include "chars.h"
#include "colors.h"
#include "initial.h"
#include <map>

/**
 * abstract class that represents a cellular automaton
 * @author Alex Cole
 */
class CellularAutomaton
{
private:
	/**
	 * The terrain of the automaton
	 */
	Range* terrain;

	/**
	 * The window of the automaton
	 */
	Range* window;

	/**
	 * Character values for the automaton
	 */
	Chars *chars;

	/**
	 * Color values for the automaton
	 */
	Colors *colors;

	/**
	 * Initial cell values for the automaton
	 */
	Initial *initial;

	/**
	 * The name of the automaton
	 */
	string name;
	
public:
	/**
	 * Default constructor that sets values
	 * to NULL and the name to an empty string.
	 */
	CellularAutomaton();

	/**
	 * Constructs a cellular automaton with a given
	 * automaton struct.
	 * @param automatonStruct
	 *			The automaton struct.
	 */
	CellularAutomaton(string automatonStruct);

	/**
	 * Destructor
	 */
	virtual ~CellularAutomaton();

	/**
	 * Copy constructor.
	 * @param automaton 
	 *			The automaton to be copied.
	 */
	CellularAutomaton(const CellularAutomaton &automaton);

	/**
	 * Overloaded assignment operator
	 * @param automaton 
	 *			The automaton to be copied
	 * @return 
	 *			A copy of the the given automaton
	 */
	CellularAutomaton& operator=(const CellularAutomaton &automaton);

	/**
	 * Gets the terrain.
	 * @return 
	 *			A pointer to the terrain.
	 */
	Range* getTerrain() const; 

	/**
	 * Gets the window.
	 * @return 
	 *			A pointer to the window.
	 */
	Range* getWindow() const; 

	/**
	 * Gets the chars.
	 * @return 
	 *			A pointer to the chars.
	 */
	Chars* getChars() const;

	/**
	 * Gets the colors.
	 * @return 
	 *			A pointer to the colors.
	 */
	Colors* getColors() const;

	/**
	 * Gets the initial.
	 * @return 
	 *			A pointer to the initial.
	 */
	Initial* getInitial() const;

	/**
	 * Gets the name.
	 * @return 
	 *			The name of the automaton.
	 */
	string getName() const;

	/**
	 * Sets Chars to the given Chars
	 * @param chars
	 * 			The given Chars to set Chars to.
	 * /
	void setChars(Chars *chars);

	/**
	 * Sets Colors to the given Colors
	 * @param colors
	 * 			The given Colors to set Colors to.
	 * /
	void setColors(Colors *colors);

	/**
	 * Sets Initial to the given Initial
	 * @param initial
	 * 			The given Initial to set Initial to.
	 * /
	void setInitial(Initial *initial);

	/**
	 * Updates the window with the given ranges. If both are empty
	 * the window is not updated. If at least one is a range, then the
	 * window is updated and the other range is set to the terrain range
	 * value.
	 * @param xRange 
	 *				The window x range.
	 * @param yRange 
	 *				The window y range.
	 */
	void updateWindow(string xRange, string yRange);

	/**
	 * Updates the terrain with the given ranges if the
	 * ranges are not empty.
	 * @param xRange
	 *				The Terrain x range.
	 * @param yRange
	 *				The Terrain y range.
	 */
	void updateTerrain(string xRange, string yRange);

	/**
	 * Sets the name of the automaton.
	 * @param name 
	 *				The given name to set the name value.
	 */
	void setName(string name);

	/**
	 * Not implemented.
	 * Determines the next state of a given cell based on the world
	 * and neighboring cells.
	 * @param world
	 *				The grid of cells.
	 * @param cell
	 *				The cell that the next state needs to be determined.
	 * @return
	 *				The next state of the cell.
	 */
	virtual State nextCellState(vector<vector<Cell>> &world, Cell &cell) = 0;

	/**
	 * Not implemented.
	 * Gets the char representation of the state of the given cell.
	 * @param cell
	 *				The cell to get the char value of.
	 * @return
	 *				The char representation of the state of the cell.
	 */
	virtual char getChar(Cell &cell) = 0;

	/**
	 * Not implemented.
	 * Gets the color representation of the state of the given cell.
	 * @param cell
	 *				The cell to get the color value of.
	 * @return
	 *				The color representation of the state of the cell.
	 */
	virtual Color getColor(Cell &cell) = 0;

	/**
	 * Not implemented.
	 * Creates a string in the automaton file format.
	 * @return 
	 *				String representation of automaton file
	 */
	virtual string toString() = 0;

protected:
	/**
	 * Sets the instance variables to default values.
	 */
	void setToDefaults();
};

#endif
