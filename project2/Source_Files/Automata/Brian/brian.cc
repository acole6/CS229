#include "brian.h"
#include "brianchars.h"
#include "briancolors.h"
#include "brianinitial.h"
#include "automatonparser.h"
#include <sstream>

/**
 * Implementation of brian.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets values
 * to NULL and the name to an empty string.
 */
Brian::Brian()
    : CellularAutomaton()
{}

/**
 * Takes in a string brian automaton struct and sets the values to
 * the values in the struct
 * @param brianStruct
 *              The string brian automaton struct
 */
Brian::Brian(string brianStruct)
    : CellularAutomaton(brianStruct)
{
    map<string, string> brian = AutomatonParser::parse(brianStruct);
    setChars(new BrianChars(AutomatonParser::getValue(brian, "Chars", true)));
    setColors(new BrianColors(AutomatonParser::getValue(brian, "Colors", true)));
    setInitial(new BrianInitial(AutomatonParser::getValue(brian, "Initial", true), getTerrain()));
}

/**
 * Copy constructor.
 * @param brian
 *              The brian automaton to be copied.
 */
Brian::Brian(const Brian &brian)
    : CellularAutomaton(brian)
{
    setChars(brian.getChars() != NULL ? new BrianChars(*((BrianChars*) brian.getChars())) : NULL);
    setColors(brian.getColors() != NULL ? new BrianColors(*((BrianColors*) brian.getColors())) : NULL);
    setInitial(brian.getInitial() != NULL ? new BrianInitial(*((BrianInitial*) brian.getInitial())) : NULL);
}

/**
 * Destructor
 */
Brian::~Brian() {}

/**
 * Overloaded assignment operator.
 * @param brian
 *               The brian automaton to be copied.
 * @return
 *              A copy of the brian automaton.
 */
Brian& Brian::operator=(const Brian &brian)
{
    if(this == &brian) return *this;
    CellularAutomaton::operator=(brian);
    setChars(brian.getChars() != NULL ? new BrianChars(*((BrianChars*) brian.getChars())) : NULL);
    setColors(brian.getColors() != NULL ? new BrianColors(*((BrianColors*) brian.getColors())) : NULL);
    setInitial(brian.getInitial() != NULL ? new BrianInitial(*((BrianInitial*) brian.getInitial())) : NULL);
    return *this;
}

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
State Brian::nextCellState(vector<vector<Cell>> &world, Cell &cell)
{
    State state = cell.getState();
    if(state == State::FIRING) return State::DEFAULT;
    if(state == State::DEFAULT) return State::READY;

    int count = 0;
    int row = cell.getX();
    int col = cell.getY();
    int rows = world.size();
    int columns = world[0].size();

    int minusRow = (row - 1) < 0 ? rows - 1 : row -1; //wrap around values
    int plusRow = (row + 1) >= rows ? 0 : row + 1;
    int minusCol = (col - 1) < 0 ? columns -1 : col - 1;
    int plusCol = (col + 1) >= columns ? 0 : col + 1;

    if(world[minusRow][col].getState() == State::FIRING) count++; //checks each of the 8 neighbors
    if(world[row][minusCol].getState() == State::FIRING) count++;
    if(world[plusRow][col].getState() == State::FIRING) count++;
    if(world[row][plusCol].getState() == State::FIRING) count++;
    if(world[plusRow][minusCol].getState() == State::FIRING) count++;
    if(world[plusRow][plusCol].getState() == State::FIRING) count++;
    if(world[minusRow][minusCol].getState() == State::FIRING) count++;
    if(world[minusRow][plusCol].getState() == State::FIRING) count++;

    if(count == 2) return State::FIRING;

    return State::READY;
}

/**
 * Gets the char representation of the state of the given cell.
 * @param cell
 *              The cell to get the char value of.
 * @return
 *              The char representation of the state of the cell.
 */
char Brian::getChar(Cell &cell)
{
    BrianChars *brianChars = (BrianChars*) getChars();
    State state = cell.getState();
    if(state == State::READY)
    {
        return (char) brianChars->getReadyChar();
    }
    else if(state == State::FIRING)
    {
        return (char) brianChars->getFiringChar();
    }
    return (char) brianChars->getDefaultChar();
}


/**
 * Gets the color representation of the state of the given cell.
 * @param cell
 *              The cell to get the color value of.
 * @return
 *              The color representation of the state of the cell.
 */
Color Brian::getColor(Cell &cell)
{
    BrianColors *brianColors = (BrianColors*) getColors();
    State state = cell.getState();
    if(state == State::READY)
    {
        return *(brianColors->getReadyColor());
    }
    else if(state == State::FIRING)
    {
        return *(brianColors->getFiringColor());
    }
    return *(brianColors->getDefaultColor());
}

/**
 * Creates a string in the automaton file format.
 * @return
 *              String representation of automaton file
 */
string Brian::toString()
{
    ostringstream ret;
    ret << "Brian =\n{\n\t";
    if(getName().length() > 0)
    {
        ret << "Name = \"" << getName() << "\";\n\n\t";
    }

    ret << getTerrain()->toString("Terrain") << "\n\n\t";

    if(getWindow() != NULL)
    {
        ret << getWindow()->toString("Window") << "\n\n\t";
    }

    ret << getChars()->toString() << "\n\n\t" << getColors()->toString() << "\n\n\t" << getInitial()->toString() << "\n};";
    return ret.str();
}
