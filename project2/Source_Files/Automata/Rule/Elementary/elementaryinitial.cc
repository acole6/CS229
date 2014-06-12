#include "elementaryinitial.h"
#include "automatonparser.h"
#include "stdlib.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of elementaryinitial.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets initial cells to 0.
 */
ElementaryInitial::ElementaryInitial() {}

/**
 * Constructor that sets the initial cells to the given cells.
 * @param cells 
 *				The given cells to assign the initial cells.
 */
ElementaryInitial::ElementaryInitial(vector<Cell> cells)
	: Initial(cells)
{}

/**
 * Constructor that takes in a elementary initial strcut and terrain
 * to set the initial cells based on automaton terrain.
 * @param elementaryInitialStruct 
 *				The elementary initial struct string
 * @param terrain
 *				The elementary automaton terrain.
 */
ElementaryInitial::ElementaryInitial(string elementaryInitialStruct, Range *terrain)
{
	map<string, string> initial  = AutomatonParser::parse(elementaryInitialStruct);
	convertCellStr(AutomatonParser::getValue(initial, "One"), terrain, State::ONE);
}

/**
 * Copy constructor
 * @param elementaryInitial 
 *				The elementary initial to be copied.
 */
ElementaryInitial::ElementaryInitial(const ElementaryInitial &elementaryInitial)
	: Initial(elementaryInitial)
{}

/**
 * Destructor
 */
ElementaryInitial::~ElementaryInitial() {}

/**
 * Overloaded assignment operator.
 * @param elementaryInitial 
 *				The elementary initial to be copied.
 * @return 
 *				A copy of elementary initial.
 */
ElementaryInitial& ElementaryInitial::operator=(const ElementaryInitial &elementaryInitial)
{
	if(this == &elementaryInitial) return *this;
	Initial::operator=(elementaryInitial);
	return *this;
}

/**
 * Creates a string elementary initial struct in the form of Initial = { One = cells; };
 * @return 
 *				A string representation of elementary initial struct.
 */
string ElementaryInitial::toString()
{
	vector<Cell> elementaryCells = getCells();
	ostringstream ret;
	ret  << "Initial = {\n\t\tOne = ";
	for(unsigned int i = 0; i < elementaryCells.size(); i++)
	{
		if(i != elementaryCells.size() - 1)
		{
			ret << elementaryCells[i].toString() << ", ";
		}
		else
		{
			ret << elementaryCells[i].toString();
		}
	}
	ret << ";\n\t};";
	return ret.str();
}
