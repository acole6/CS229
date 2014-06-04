#ifndef RULEAUTOMATON_H
#define RULEAUTOMATON_H

#include "cellularautomaton.h"

const int InvalidRuleException = 6;

/**
 * abstract class that represents a cellular automaton with a rule
 */
class RuleAutomaton : public CellularAutomaton
{
protected:
	/**
	 * rule for the cellular automaton
	 */
	string rule;

public:
	/**
	 * Default constructor sets initial values to NULL and
	 * the rule to an empty string.
	 */
	RuleAutomaton();

	/**
	 * Takes in rule automaton struct and assigns values from struct
	 * to rule automaton.
	 * @param ruleAutomatonStruct
	 *				The string rule automaton struct.
	 */
	RuleAutomaton(string ruleAutomatonStruct);

	/**
	 * Destructor
	 */
	virtual ~RuleAutomaton();

	/**
	 * Copy constructor.
	 * @param ruleAutomaton
	 *				The rule automaton to be copied.
	 */
	RuleAutomaton(const RuleAutomaton &ruleAutomaton);

	/**
	 * Overloaded assignment operator.
	 * @param ruleAutomaton
	 *				The rule automaton to be copied.
	 * @return
	 *				A copy of the rule automaton.
	 */
	RuleAutomaton& operator=(const RuleAutomaton &ruleAutomaton);

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
	 * Gets the rule.
	 * @return
	 *				The rule as a string.
	 */
	string getRule();

	/**
	 * Sets the rule with the given rule string
	 * @param rule
	 *				The rule string to set the rule to.
	 */
	void setRule(string rule);

	/**
	 * Not implemented.
	 * Creates a string in the automaton file format.
	 * @return 
	 *				String representation of automaton file
	 */
	virtual string toString() = 0;
};

#endif
