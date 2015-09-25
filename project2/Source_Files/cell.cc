#include "cell.h"
#include <sstream>

/**
* Implementation of cell.h
* @author Alex Cole
*/

/**
 * Default constructor that sets state to Default
 * and x and y values to 0.
 */
Cell::Cell()
{
    x = 0;
    y = 0;
    state = State::DEFAULT;
}

/**
 * Sets x, y and state to given values.
 * @param x
 *          The x position.
 * @param y
 *          The y position.
 * @param state
 *          The state of the cell.
 */
Cell::Cell(int x, int y, State state)
{
    this->x = x;
    this->y = y;
    this->state = state;
}

/**
 * Copy constructor.
 * @param cell
 *          The cell to be copied.
 */
Cell::Cell(const Cell &cell)
{
    x = cell.x;
    y = cell.y;
    state = cell.state;
}

/**
 * Destructor
 */
Cell::~Cell() {}

/**
 * Overloaded assignment operator.
 * @param cell
 *          The cell to be copied.
 * @return
 *          A copy of the given cell.
 */
Cell& Cell::operator=(const Cell &cell)
{
    if(this == &cell) return *this;
    x = cell.x;
    y = cell.y;
    state = cell.state;
    return *this;
}

/**
 * Gets the x position.
 * @return
 *          The x value.
 */
int Cell::getX()
{
    return x;
}

/**
 * Gets the y position.
 * @return
 *          The y value.
 */
int Cell::getY()
{
    return y;
}

/**
 * Gets the state.
 * @return
 *          The state of the cell.
 */
State Cell::getState()
{
    return state;
}

/**
 * Sets the x position.
 * @param x
 *          The value x is to be set to.
 */
void Cell::setX(int x)
{
    this->x = x;
}

/**
 * Sets the y position.
 * @param y
 *          The value y is to be set to.
 */
void Cell::setY(int y)
{
    this->y = y;
}

/**
 * Sets the state.
 * @param state
 *          The state the cell is to be set to.
 */
void Cell::setState(State state)
{
    this->state = state;
}


/**
 * Checks to see if cells are equal by only
 * comparing the x and y values.
 * @param cell
 *          The cell to be compared.
 * @return
 *          True if x and y values are the same otherwise false.
 */
bool Cell::equals(Cell &cell)
{
    return this->x == cell.x && this->y == cell.y;
}

/**
 * Cell as a string in the form of (x, y).
 * @return
 *          String representation of a cell.
 */
string Cell::toString()
{
    ostringstream ret;
    ret << "(" << x << ", " << y << ")";
    return ret.str();
}
