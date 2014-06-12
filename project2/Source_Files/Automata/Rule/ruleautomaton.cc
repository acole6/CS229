#include "ruleautomaton.h"
#include "automatonparser.h"

/**
 * Implementation of ruleautomaton.h
 * @author Alex Cole
 */

/**
 * Default constructor sets initial values to NULL and
 * the rule to an empty string.
 */
RuleAutomaton::RuleAutomaton()
	: CellularAutomaton()
{
	rule = "";
}

/**
 * Takes in rule automaton struct and assigns values from struct
 * to rule automaton.
 * @param ruleAutomatonStruct
 *				The string rule automaton struct.
 */
RuleAutomaton::RuleAutomaton(string ruleAutomatonStruct)
	: CellularAutomaton(ruleAutomatonStruct)
{
	map<string, string> ruleAutomaton = AutomatonParser::parse(ruleAutomatonStruct);
	rule = AutomatonParser::getValue(ruleAutomaton, "Rule", true);
}

/**
 * Destructor
 */
RuleAutomaton::~RuleAutomaton() {}

/**
 * Copy constructor.
 * @param ruleAutomaton
 *				The rule automaton to be copied.
 */
RuleAutomaton::RuleAutomaton(const RuleAutomaton &ruleAutomaton)
	: CellularAutomaton(ruleAutomaton)
{
	rule = ruleAutomaton.rule;
}

/**
 * Overloaded assignment operator.
 * @param ruleAutomaton
 *				The rule automaton to be copied.
 * @return
 *				A copy of the rule automaton.
 */
RuleAutomaton& RuleAutomaton::operator=(const RuleAutomaton &ruleAutomaton)
{
	if(this == &ruleAutomaton) return *this;
	CellularAutomaton::operator=(ruleAutomaton);
	rule = ruleAutomaton.rule;
	return *this;
}

/**
 * Gets the rule.
 * @return
 *				The rule as a string.
 */
string RuleAutomaton::getRule() const
{
	return rule;
}

/**
 * Sets the rule with the given rule string
 * @param rule
 *				The rule string to set the rule to.
 */
void RuleAutomaton::setRule(string rule)
{
	this->rule = rule;
}
