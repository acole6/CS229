#include "elementary.h"
#include "elementarychars.h"
#include "elementarycolors.h"
#include "elementaryinitial.h"
#include "automatonparser.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of elementary.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets values
 * to NULL and the name and rule to an empty string.
 */
Elementary::Elementary()
	: RuleAutomaton()
{}

/**
 * Takes in a string elementary struct and sets the values to
 * the values in the struct.
 * @param elementaryStruct 
 *					The string elementary struct
 * @throws InvalidRuleException
 *					If rule is not in the range 0-255 (inclusive).
 */
Elementary::Elementary(string elementaryStruct)
	: RuleAutomaton(elementaryStruct)
{
	map<string, string> elementary = AutomatonParser::parse(elementaryStruct);
	if(!validRule()) 
	{
		cerr << "Invalid rule: " << getRule() << endl;
		throw InvalidRuleException;
	}
	setChars(new ElementaryChars(AutomatonParser::getValue(elementary, "Chars", true)));
	setColors(new ElementaryColors(AutomatonParser::getValue(elementary, "Colors", true)));
	setInitial(new ElementaryInitial(AutomatonParser::getValue(elementary, "Initial",true), getTerrain()));
}

/**
 * Copy constructor.
 * @param elementary 
 *					The elementary automaton to be copied.
 */
Elementary::Elementary(const Elementary &elementary)
	: RuleAutomaton(elementary)
{
	setChars(elementary.getChars() != NULL ? new ElementaryChars(*((ElementaryChars*) elementary.getChars())) : NULL);
	setColors(elementary.getColors() != NULL ? new ElementaryColors(*((ElementaryColors*) elementary.getColors())) : NULL);
	setInitial(elementary.getInitial() != NULL ? new ElementaryInitial(*((ElementaryInitial*) elementary.getInitial())) : NULL);
}

/**
 * Destructor
 */
Elementary::~Elementary() {}

/**
 * Overloaded assignment operator.
 * @param elementary 
 *					The elementary automaton to be copied.
 * @return 
 *					A copy of the elementary automaton.
 */
Elementary& Elementary::operator=(const Elementary &elementary)
{
	if(this == &elementary) return *this;
	RuleAutomaton::operator=(elementary);
	setChars(elementary.getChars() != NULL ? new ElementaryChars(*((ElementaryChars*) elementary.getChars())) : NULL);
	setColors(elementary.getColors() != NULL ? new ElementaryColors(*((ElementaryColors*) elementary.getColors())) : NULL);
	setInitial(elementary.getInitial() != NULL ? new ElementaryInitial(*((ElementaryInitial*) elementary.getInitial())) : NULL);
	return *this;
}

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
State Elementary::nextCellState(vector<vector<Cell>> &world, Cell &cell)
{
	if(cell.getState() == State::ONE) return State::ONE;

	string pattern = rulePattern(world, cell);
	unsigned char stateRule = atoi(getRule().c_str());
	if((pattern.compare("111") == 0 && getBit(stateRule, 7) == 1) || (pattern.compare("110") == 0 && getBit(stateRule, 6) == 1) || (pattern.compare("101") == 0 && getBit(stateRule, 5) == 1)
		|| (pattern.compare("100") == 0 && getBit(stateRule, 4) == 1) || (pattern.compare("011") == 0 && getBit(stateRule, 3) == 1) || (pattern.compare("010") == 0 && getBit(stateRule, 2) == 1)
		|| (pattern.compare("001") == 0 && getBit(stateRule, 1) == 1) || (pattern.compare("000") == 0 && getBit(stateRule, 0) == 1))
	{
		return State::ONE; //if the pattern has a new state of ONE, return state of ONE
	}
	return State::DEFAULT;
}

/**
 * Gets the char representation of the state of the given cell.
 * @param cell
 *				The cell to get the char value of.
 * @return
 *				The char representation of the state of the cell.
 */
char Elementary::getChar(Cell &cell)
{
	ElementaryChars *elementaryChars = (ElementaryChars*) getChars();
	if(cell.getState() == State::ONE)
	{
		return (char) elementaryChars->getOneChar();
	}
	return (char) elementaryChars->getDefaultChar();
}

/**
 * Gets the color representation of the state of the given cell.
 * @param cell
 *				The cell to get the color value of.
 * @return
 *				The color representation of the state of the cell.
 */
Color Elementary::getColor(Cell &cell)
{
	ElementaryColors *elementaryColors = (ElementaryColors*) getColors();
	if(cell.getState() == State::ONE)
	{
		return *(elementaryColors->getOneColor());
	}
	return *(elementaryColors->getDefaultColor());
}

/**
 * Creates a string in the automaton file format.
 * @return 
 *				String representation of automaton file
 */
string Elementary::toString()
{
	ostringstream ret;
	ret << "Elementary =\n{\n\t";
	if(getName().length() > 0)
	{
		ret << "Name = \"" << getName() << "\";\n\n\t";
	}

	if(!getRule().empty())
	{
		ret << "Rule = " << getRule() << ";\n\n\t";
	}

	ret << getTerrain()->toString("Terrain") << "\n\n\t"; 

	if(getWindow() != NULL)
	{
		ret << getWindow()->toString("Window") << "\n\n\t";
	}
			
	ret << getChars()->toString() << "\n\n\t" << getColors()->toString() << "\n\n\t" << getInitial()->toString() << "\n};";
	return ret.str();
}

/**
 * Gets the bit value in an unsigned char at the given position.
 * @param ch
 *				The character to get a bit at a specific position.
 * @param pos
 *				The position of the bit to get.
 * @return
 *				The value of the bit (1 or 0) as an int.
 */
int Elementary::getBit(unsigned char ch, int pos)
{
	return (ch & (1 << pos)) != 0;
}

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
string Elementary::rulePattern(vector<vector<Cell>> &world, Cell &cell)
{
	int row = cell.getX();
	int col = cell.getY();
	int rows = world.size();
	int columns = world[0].size();

	int minusRow = (row - 1) < 0 ? rows - 1 : row - 1; //wrap around values
	int minusCol = (col - 1) < 0 ? columns -1 : col - 1;
	int plusCol = (col + 1) >= columns ? 0 : col + 1;

	string pattern; //checks the state of the cells above the given cell (accounting for wrap around)
	pattern = world[minusRow][minusCol].getState() == State::ONE ? pattern + "1" : pattern + "0";
	pattern = world[minusRow][col].getState() == State::ONE ? pattern + "1" : pattern + "0";
	pattern = world[minusRow][plusCol].getState() == State::ONE ? pattern + "1" : pattern + "0";
	return pattern;
}

/**
 * Checks to see if the rule is a valid rule in the range 0-255 (inclusive).
 * @return
 *				True if valid otherwise false.
 */
bool Elementary::validRule()
{
	int num = atoi(getRule().c_str());
	return num >= 0 && num <= 255;
}
