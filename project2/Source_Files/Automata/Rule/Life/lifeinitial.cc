#include "lifeinitial.h"
#include "automatonparser.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>
#include <cmath>

/**
 * Implementation of lifeinitial.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets initial cells to 0.
 */
LifeInitial::LifeInitial() {}

/**
 * Constructor that sets the initial cells to the given cells.
 * @param cells 
 *				The given cells to assign the initial cells.
 */
LifeInitial::LifeInitial(vector<Cell> cells)
	: Initial(cells)
{}

/**
 * Constructor that takes in a like-like initial struct and terrain
 * to set the initial cells based on automaton terrain.
 * @param lifeInitialStruct 
 *				The life-like initial struct string
 * @param terrain
 *				The life-like automaton terrain.
 */
LifeInitial::LifeInitial(string lifeInitialStruct, Range *terrain)
{
	map<string, string> initial  = AutomatonParser::parse(lifeInitialStruct);
	convertCellStr(AutomatonParser::getValue(initial, "Alive"), terrain, State::ALIVE);
}

/**
 * Copy constructor
 * @param lifeInitial 
 *				The life-like initial to be copied.
 */
LifeInitial::LifeInitial(const LifeInitial &lifeInitial)
	: Initial(lifeInitial)
{}

/**
 * Destructor
 */
LifeInitial::~LifeInitial() {}

/**
 * Overloaded assignment operator.
 * @param lifeInitial 
 *				The life-like initial to be copied.
 * @return 
 *				A copy of life-like initial.
 */
LifeInitial& LifeInitial::operator=(const LifeInitial &lifeInitial)
{
	if(this == &lifeInitial) return *this;
	Initial::operator=(lifeInitial);
	return *this;
}

/**
 * Creates a string life-like initial struct in the form of Initial = { Alive = cells; };
 * @return 
 *				A string representation of life-like initial struct.
 */
string LifeInitial::toString()
{
	vector<Cell> lifeCells = getCells();
	ostringstream ret;
	ret  << "Initial = {\n\t\tAlive = ";
	for(unsigned int i = 0; i < lifeCells.size(); i++)
	{
		if(i != lifeCells.size() - 1)
		{
			ret << lifeCells[i].toString() << ", ";
		}
		else
		{
			ret << lifeCells[i].toString();
		}
	}
	ret << ";\n\t};";
	return ret.str();
}
