#include "lifeclass.h"
#include "lifeinitial.h"
#include "lifechars.h"
#include "lifecolors.h"
#include "automatonparser.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of lifeclass.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets values
 * to NULL and the name to an empty string.
 */
Life::Life()
	: RuleAutomaton()
{}

/**
 * Takes in a string life-like automaton struct and sets the values to
 * the values in the struct
 * @param lifeStruct 
 *				The string life-like automaton struct
 */
Life::Life(string lifeStruct)
	: RuleAutomaton(lifeStruct)
{
	map<string, string> life = AutomatonParser::parse(lifeStruct);
	setBorn();
	setStayAlive();
	setChars(new LifeChars(AutomatonParser::getValue(life, "Chars", true)));
	setColors(new LifeColors(AutomatonParser::getValue(life, "Colors", true)));
	setInitial(new LifeInitial(AutomatonParser::getValue(life, "Initial", true), getTerrain()));
}

/**
 * Copy constructor.
 * @param life 
 *				The like-like automaton to be copied.
 */
Life::Life(const Life &life)
	: RuleAutomaton(life)
{
	born = life.born;
	stayAlive = life.stayAlive;
	setChars(life.getChars() != NULL ? new LifeChars(*((LifeChars*) life.getChars())) : NULL);
	setColors(life.getColors() != NULL ? new LifeColors(*((LifeColors*) life.getColors())) : NULL);
	setInitial(life.getInitial() != NULL ? new LifeInitial(*((LifeInitial*) life.getInitial())) : NULL);
}

/**
 * Destructor
 */
Life::~Life() {}

/**
 * Overloaded assignment operator.
 * @param life 
 *				 The life-like automaton to be copied.
 * @return 
 *				A copy of the life-like automaton.
 */
Life& Life::operator=(const Life &life)
{
	if(this == &life) return *this;
	RuleAutomaton::operator=(life);
	born = life.born;
	stayAlive = life.stayAlive;
	setChars(life.getChars() != NULL ? new LifeChars(*((LifeChars*) life.getChars())) : NULL);
	setColors(life.getColors() != NULL ? new LifeColors(*((LifeColors*) life.getColors())) : NULL);
	setInitial(life.getInitial() != NULL ? new LifeInitial(*((LifeInitial*) life.getInitial())) : NULL);
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
State Life::nextCellState(vector<vector<Cell>> &world, Cell &cell)
{
	int count = 0;
	int row = cell.getX();
	int col = cell.getY();
	int rows = world.size();
	int columns = world[0].size();

	int minusRow = (row - 1) < 0 ? rows - 1 : row -1; //wrap around values
	int plusRow = (row + 1) >= rows ? 0 : row + 1;
	int minusCol = (col - 1) < 0 ? columns -1 : col - 1;
	int plusCol = (col + 1) >= columns ? 0 : col + 1;

	if(world[minusRow][col].getState() == State::ALIVE) count++; //checks each of the 8 neighbors
	if(world[row][minusCol].getState() == State::ALIVE) count++;
	if(world[plusRow][col].getState() == State::ALIVE) count++;
	if(world[row][plusCol].getState() == State::ALIVE) count++;
	if(world[plusRow][minusCol].getState() == State::ALIVE) count++;
	if(world[plusRow][plusCol].getState() == State::ALIVE) count++;
	if(world[minusRow][minusCol].getState() == State::ALIVE) count++;
	if(world[minusRow][plusCol].getState() == State::ALIVE) count++;

	if(isBorn(count) || (cell.getState() == State::ALIVE && staysAlive(count))) return State::ALIVE;

	return State::DEFAULT;
}
/**
 * Gets the char representation of the state of the given cell.
 * @param cell
 *				The cell to get the char value of.
 * @return
 *				The char representation of the state of the cell.
 */
char Life::getChar(Cell &cell)
{
	LifeChars *lifeChars = (LifeChars*) getChars();
	if(cell.getState() == State::ALIVE)
	{
		return (char) lifeChars->getAliveChar();
	}
	return (char) lifeChars->getDefaultChar();
}

/**
 * Gets the color representation of the state of the given cell.
 * @param cell
 *				The cell to get the color value of.
 * @return
 *				The color representation of the state of the cell.
 */
Color Life::getColor(Cell &cell)
{
	LifeColors* lifecolors = (LifeColors*) getColors();
	if(cell.getState() == State::ALIVE)
	{
		return *(lifecolors->getAliveColor());
	}
	return *(lifecolors->getDefaultColor());
}

/**
 * Creates a string in the automaton file format.
 * @return 
 *				String representation of automaton file
 */
string Life::toString()
{
	ostringstream ret;
	ret << "Life =\n{\n\t";
	if(getName().length() > 0)
	{
		ret << "Name = \"" << getName() << "\";\n\n\t";
	}

	if(getRule().length() > 0)
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
 * Adds values to the born int vector based on the rule string.
 * @throws InvalidRuleException
 *				If the rule is not in valid format (B012../S012..)
 */
void Life::setBorn()
{
	string ruleStr = getRule();
	if(ruleStr[0] != 'B')
	{
		cerr << "Invalid rule: " << ruleStr << endl;
		throw InvalidRuleException;
	}
	
	int split = ruleStr.find("/");
	if(split == string::npos)
	{
		cerr << "Invalid rule: " << ruleStr << endl;
		throw InvalidRuleException;
	}

	fillVectorFromDigitStr(born, ruleStr.substr(0, split));
	if(born.size() == 0)
	{
		cerr << "Invalid rule: " << ruleStr << endl;
		throw InvalidRuleException;
	}
}

/**
 * Adds values to the stayAlive int vector based on the rule string.
 * @throws InvalidRuleException
 *				If the rule is not in valid format (B012../S012..)
 */
void Life::setStayAlive()
{
	string ruleStr = getRule();
	int split = ruleStr.find("/");
	if(split == string::npos)
	{
		cerr << "Invalid rule: " << ruleStr << endl;
		throw InvalidRuleException;
	}

	if(split + 1 >= ruleStr.length() || ruleStr[split + 1] != 'S')
	{ 
		cerr << "Invalid rule: " << ruleStr << endl;
		throw InvalidRuleException;
	}
	
	fillVectorFromDigitStr(stayAlive, ruleStr.substr(split + 1, ruleStr.length()));
	if(stayAlive.size() == 0)
	{
		cerr << "Invalid rule: " << ruleStr << endl;
		throw InvalidRuleException;
	}
}

/**
 * Adds digits to int vector from a string of digits.
 * @param digits
 *				The int vector for the digits to be added.
 * @param digitStr
 *				The string of digits.
 * @throws InvalidRuleException
 *				If one of the digits is not in the range 0-8 (inclusive).
 */
void Life::fillVectorFromDigitStr(vector<int> &digits, string digitStr)
{
	for(int i = 1; i < digitStr.length(); i++)
	{
		int num = digitStr[i] - '0';
		if(num < 0 || num > 8)
		{
			cerr << "Invalid rule: " << getRule() << endl;
			throw InvalidRuleException;
		}
		digits.push_back(num);
	}
}

/**
 * Checks to see if the value is in the born vector.
 * @param count
 *				The value to be checked.
 * @return
 *				True if it is in the vector otherwise false.
 */
bool Life::isBorn(int count)
{
	return foundCount(born, count);
}

/**
 * Checks to see if the value is in the sayAlive vector.
 * @param count
 *				The value to be checked.
 * @return
 *				True if it is in the vector otherwise false.
 */
bool Life::staysAlive(int count)
{
	return foundCount(stayAlive, count);
}

/**
 * Checks to see if the value is in an int vector.
 * @param nums
 *				The int vector.
 * @param count
 *				The value to be checked.
 * @return
 *				True if it is in the vector otherwise false.
 */
bool Life::foundCount(vector<int> &nums, int count)
{
	for(unsigned int i = 0; i < nums.size(); i++)
	{
		if(count == nums[i]) return true;
	}
	return false;
}
