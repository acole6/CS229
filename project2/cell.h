#ifndef CELL_H
#define CELL_H

#include <string>

using namespace std;

/**
 * class to store x and y value of a cell, as well as its state.
 * State is an emum class with states of Default, Alive, Ready, Firing and One
 * @author Alex Cole
 */
enum class State : int { DEFAULT = 1, ALIVE = 2, READY = 3, FIRING = 4, ONE = 5 };

class Cell
{
	/**
	 * x position of the cell
	 */
	int x;

	/**
	 * y position of the cell
	 */
	int y;

	/**
	 * state of the cell
	 */
	State state;
	
public:
	/**
	 * Default constructor that sets state to Default 
	 * and x and y values to 0.
	 */
	Cell();

	/**
	 * Sets x, y and state to given values.
	 * @param x 
	 *			The x position.
	 * @param y 
	 *			The y position.
	 * @param state 
	 *			The state of the cell.
	 */
	Cell(int x, int y, State state);

	/**
	 * Copy constructor.
	 * @param cell 
	 *			The cell to be copied.
	 */
	Cell(const Cell &cell);

	/**
	 * Destructor
	 */
	~Cell();

	/**
	 * Overloaded assignment operator.
	 * @param cell 
	 *			The cell to be copied.
	 * @return 
	 *			A copy of the given cell.
	 */
	Cell& operator=(const Cell &cell);

	/**
	 * Gets the x position.
	 * @return 
	 *			The x value.
	 */
	int getX();

	/**
	 * Gets the y position.
	 * @return 
	 *			The y value.
	 */
	 int getY();

	/**
	 * Gets the state.
	 * @return 
	 *			The state of the cell.
	 */
	State getState();

	/**
	 * Sets the x position.
	 * @param x 
	 *			The value x is to be set to.
	 */
	void setX(int x);

	/**
	 * Sets the y position.
	 * @param y 
	 *			The value y is to be set to.
	 */
	void setY(int y);

	/**
	 * Sets the state.
	 * @param state 
	 *			The state the cell is to be set to.
	 */
	void setState(State state);

	/**
	 * Checks to see if cells are equal by only
	 * comparing the x and y values.
	 * @param cell 
	 *			The cell to be compared.
	 * @return 
	 *			True if x and y values are the same otherwise false.
	 */
	bool equals(Cell &cell);

	/**
	 * Cell as a string in the form of (x, y).
	 * @return 
	 *			String representation of a cell.
	 */
	string toString();
};

#endif
