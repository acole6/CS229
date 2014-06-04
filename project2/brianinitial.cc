#include "brianinitial.h"
#include "automatonparser.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of brianinitial.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets initial cells to 0.
 */
BrianInitial::BrianInitial() {}

/**
 * Constructor that sets the initial cells to the given cells.
 * @param cells 
 *				The given cells to assign the initial cells.
 */
BrianInitial::BrianInitial(vector<Cell> cells)
	: Initial(cells)
{}

/**
 * Constructor that takes in a brian initial strcut and terrain
 * to set the initial cells based on automaton terrain.
 * @param brianInitialStruct 
 *				The brian initial struct string
 * @param terrain
 *				The brian automaton terrain.
 */
BrianInitial::BrianInitial(string brianInitialStruct, Range *terrain)
{
	map<string, string> initial  = AutomatonParser::parse(brianInitialStruct);
	convertCellStr(AutomatonParser::getValue(initial, "Ready"), terrain, State::READY);
	convertCellStr(AutomatonParser::getValue(initial, "Firing"), terrain, State::FIRING);
}

/**
 * Copy constructor
 * @param brianInitial 
 *				The brian initial to be copied.
 */
BrianInitial::BrianInitial(const BrianInitial &brianInitial)
	: Initial(brianInitial)
{}

/**
 * Destructor
 */
BrianInitial::~BrianInitial() {}

/**
 * Overloaded assignment operator.
 * @param brianInitial 
 *				The brian initial to be copied.
 * @return 
 *				A copy of brian initial.
 */
BrianInitial& BrianInitial::operator=(const BrianInitial &brianInitial)
{
	if(this == &brianInitial) return *this;
	Initial::operator=(brianInitial);
	return *this;
}

/**
 * Creates a string brian initial struct in the form of Initial = { Ready = readyCells; Firing = firingCells; };
 * @return 
 *				A string representation of brian initial struct
 */
string BrianInitial::toString()
{
	ostringstream ret;
	ret  << "Initial = {\n";

	string ready;
	string firing;
	for(unsigned int i = 0; i < cells.size(); i++)
	{
		if(cells[i].getState() == State::READY)
		{
			if(ready.empty())
			{
				ready += cells[i].toString();
			}
			else
			{
				ready += ("," + cells[i].toString()); 
			}
		}
		else
		{
			if(firing.empty())
			{
				firing += cells[i].toString();
			}
			else
			{
				firing += ("," + cells[i].toString()); 
			}
		}
	}

	ret << "\t\tReady = " << ready << ";\n";
	ret << "\t\tFiring = " << firing << ";\n";

	ret << "\t};";
	return ret.str();
}
