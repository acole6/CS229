#include "cellularautomaton.h"
#include "automatonparser.h"
#include <iostream>

/**
 * Implementation of cellularautomaton.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets values
 * to NULL and the name to an empty string.
 */
CellularAutomaton::CellularAutomaton()
{
	setToDefaults();
}

/**
 * Constructs a cellular automaton with a given
 * automaton struct.
 * @param automatonStruct
 *			The automaton struct.
 */
CellularAutomaton::CellularAutomaton(string automatonStruct)
{
	setToDefaults();
	map<string, string> automaton = AutomatonParser::parse(automatonStruct);
	name = automaton["Name"];
	terrain = new Range(AutomatonParser::getValue(automaton, "Terrain", true));
	string windowStruct = automaton["Window"];
	if(!windowStruct.empty()) window = new Range(windowStruct);
}

/**
 * Destructor
 */
CellularAutomaton::~CellularAutomaton() 
{
	delete terrain;
	delete window;
	delete chars;
	delete colors;
	delete initial;
}

/**
 * Copy constructor.
 * @param automaton 
 *			The automaton to be copied.
 */
CellularAutomaton::CellularAutomaton(const CellularAutomaton &automaton)
{
	name = automaton.name;
	terrain = automaton.terrain != NULL ? new Range(*(automaton.terrain)) : NULL;
	window =  automaton.window != NULL ? new Range(*(automaton.window)) : NULL;
}

/**
 * Overloaded assignment operator
 * @param automaton 
 *			The automaton to be copied
 * @return 
 *			A copy of the the given automaton
 */
CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton &automaton)
{
	if(this == &automaton) return *this;
	name = automaton.name;
	terrain = automaton.terrain != NULL ? new Range(*(automaton.terrain)) : NULL;
	window =  automaton.window != NULL ? new Range(*(automaton.window)) : NULL;
	return *this;
}

/**
 * Gets the terrain.
 * @return 
 *			A pointer to the terrain.
 */
Range* CellularAutomaton::getTerrain()
{
	return terrain;
}

/**
 * Gets the window.
 * @return 
 *			A pointer to the window.
 */
Range* CellularAutomaton::getWindow() 
{
	return window;
}

/**
 * Gets the chars.
 * @return 
 *			A pointer to the chars.
 */
Chars* CellularAutomaton::getChars()
{
	return chars;
}

/**
 * Gets the colors.
 * @return 
 *			A pointer to the colors.
 */
Colors* CellularAutomaton::getColors()
{
	return colors;
}

/**
 * Gets the initial.
 * @return 
 *			A pointer to the initial.
 */
Initial* CellularAutomaton::getInitial()
{
	return initial;
}

/**
 * Gets the name.
 * @return 
 *			The name of the automaton.
 */
string CellularAutomaton::getName()
{
	return name;
}

/**
 * Updates the window with the given ranges. If both are empty
 * the window is not updated. If at least one is a range, then the
 * window is updated and the other range is set to the terrain range
 * value.
 * @param xRange 
 *				The window x range.
 * @param yRange 
 *				The window y range.
 */
void CellularAutomaton::updateWindow(string xRange, string yRange)
{
	if(!xRange.empty() && !yRange.empty()) //both ranges are not empty
	{
		if(window == NULL) window = new Range();
		window->updateRange(xRange, yRange);
	}
	else if(!xRange.empty() || !yRange.empty()) //one of the ranges is empty
	{
		if(xRange.empty() && window == NULL) //gets the terrain range if range is empty and the window is NULL
		{
			xRange = terrain->rangeStr(terrain->getXStart(), terrain->getXEnd());
		}
		if(yRange.empty() && window == NULL)
		{
			yRange = terrain->rangeStr(terrain->getYStart(), terrain->getYEnd());
		}
		if(window == NULL) window = new Range();
		window->updateRange(xRange, yRange);
	}
}

/**
 * Updates the terrain with the given ranges if the
 * ranges are not empty.
 * @param xRange
 *				The Terrain x range.
 * @param yRange
 *				The Terrain y range.
 */
void CellularAutomaton::updateTerrain(string xRange, string yRange)
{
	terrain->updateRange(xRange, yRange);
}

/**
 * Sets the name of the automaton.
 * @param name 
 *				The given name to set the name value.
 */
void CellularAutomaton::setName(string name)
{
	this->name = name;
}

/**
 * Sets the instance variables to default values.
 */
void CellularAutomaton::setToDefaults()
{
	terrain = NULL;
	window = NULL;
	chars = NULL;
	colors = NULL;
	initial = NULL;
	name = "";
}
