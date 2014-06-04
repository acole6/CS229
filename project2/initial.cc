#include "initial.h"
#include <iostream>

/**
 * Implementation of initial.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets number of initial cells to 0.
 */
Initial::Initial() {}

/**
 * Constructor that sets initial cells to the given cells.
 * @param cells
 *				The cells to set the initial cells to.
 */
Initial::Initial(vector<Cell> cells)
{
	this->cells = cells;
}

/**
 * Destructor
 */
Initial::~Initial() {}

/**
 * Copy constructor.
 * @param initial
 *				The initial to be copied.
 */
Initial::Initial(const Initial &initial)
{
	cells = initial.cells;
}

/**
 * Overloaded operator assignment.
 * @param initial
 *				The initial to be copied.
 * @return
 *				A copy of the given initial.
 */
Initial& Initial::operator=(const Initial &initial)
{
	if(this == &initial) return *this;
	cells = initial.cells;
	return *this;
}

/**
 * Gets the cells.
 * @return 
 *			A cell vector of initial cells.
 */
vector<Cell> Initial::getCells()
{
	return cells;
}

/**
 * Adds a cell to the vector of cells (does not check for duplicates).
 * @param cell 
 *				The cell to be added.
 */
void Initial::addCell(Cell cell)
{
	cells.push_back(cell);
}

/**
 * Empties the cell vector of initial cells.
 */
void Initial::clearCells()
{
	cells.clear();
}

/**
 * Gets the number of cells in the initial cell vector.
 * @return
 *				The number of cells.
 */
int Initial::size()
{
	return cells.size();
}

/**
 * Checks to see if a cell is in the vector of cells with the
 * given x and y values.
 * @param x 
 *				The x value.
 * @param y 
 *				The y value.
 * @return 
 *				True if the cell is in the vector otherwise false.
 */
bool Initial::contains(int x, int y)
{
	for(unsigned int i = 0; i < cells.size(); i++)
	{
		if(cells[i].getX() == x && cells[i].getY() == y)
		{
			return true;
		}
	}
	return false;
}

/**
 * Initializes the initial object with a given terrain range and string of cells in the form of (cell, cell, cell,...).
 * @param initialCells 
 *				The string of cells.
 * @param terrain 
 *				The automaton terrain.
 * @param state 
 *				The state to set the cells to.
 * @throws InvalidInitialValueException
 *				If there is a comma missing between cells.
 */
void Initial::convertCellStr(string initialCells, Range *terrain, State state)
{
	if(initialCells.empty()) return;
	string temp = initialCells;
	string cell = extractCellStr(temp);
	addCellFromCellStr(cell, terrain, state);
	int comma = temp.empty() ? string::npos : 0;
	while(comma == 0) //loops until there are no more cells in cell string
	{
		cell = extractCellStr(temp);
		addCellFromCellStr(cell, terrain, state);
		comma = temp.find(",");
	}
	if(comma != string::npos)
	{
		cerr << "Initial value is not formatted as Identifier = (x0,y0),(x1,y1),(x2,y2)...: " << initialCells << endl;
		throw InvalidInitialValueException;
	}
}

/**
 * Converts cells given from a world grid to cells in the automaton terrain.
 * @param worldCells
 *				The cells from the world grid to be converted.
 * @param terrain
 *				The automaton terrain.
 */
void Initial::convertToTerrainCells(vector<Cell> worldCells, Range *terrain)
{
	clearCells();
	int startTerrainY = terrain->getYEnd();
	int startTerrainX = terrain->getXStart();
	for(unsigned int i = 0; i < worldCells.size(); i++)
	{
		int xPos = worldCells[i].getY();
		int yPos = worldCells[i].getX();

		int x = startTerrainX <= 0 ? xPos - (startTerrainX * -1) : xPos + startTerrainX;
 		int y = startTerrainY <= 0 ? (yPos + (startTerrainY * -1)) * -1 : (yPos - startTerrainY) * -1;
		State state = worldCells[i].getState();
		
		Cell cell(x, y, state);
		addCell(cell);
	}
}

/**
 * Wraps a cell that is outside of the terrain to fit it into the terrain.
 * @param pos 
 *				The position in the range.
 * @param start 
 *				The start value of the range.
 * @param end 
 *				The end value of the range.
 * @return 
 *				The value of position after it has been wrapped around to be in the terrain.
 */
int Initial::fitToTerrain(int pos, int start, int end)
{
	int length = (end - start) + 1;
	if(pos < start)
	{
		int diff = abs(start - pos);
		while(diff > length) //subtracts the length of the range until the diff is <= to range
		{
			pos += length;
			diff = abs(start - pos);
		}
		pos += length; //wraps value to fit in range
	}
	else if(pos > end)
	{
		int diff = abs(pos - end);
		while(diff > length)
		{
			pos -= length;
			diff = abs(pos - end);
		}
		pos -= length;
	}
	return pos;
}

/**
 * Gets a cell string in the form of x,y from a string of cells.
 * @param initialCells
 *				The string of cells.
 * @return
 *				A string representation of a cell.
 * @throws InvalidInitialValueException
 *				If the cell is missing the left bracket '(' or the right bracket ')'
 */
string Initial::extractCellStr(string &initialCells)
{
	int leftIndex = initialCells.find("(");
	if(leftIndex == string::npos)
	{
		cerr << "Initial value is not formatted as Identifier = (x0,y0),(x1,y1),(x2,y2)...: " << initialCells << endl;
		throw InvalidInitialValueException;
	}

	int rightIndex = initialCells.find(")");
	if(rightIndex == string::npos)
	{
		cerr << "Initial value is not formatted as Identifier = (x0,y0),(x1,y1),(x2,y2)...: " << initialCells << endl;
		throw InvalidInitialValueException;
	}

	string cell = initialCells.substr(leftIndex + 1, (rightIndex - leftIndex) - 1);
	initialCells = initialCells.substr(rightIndex + 1, initialCells.length());
	return cell;
}

/**
 * Add cell from a cell string to the initial cells if it is not already in the initial cells.
 * @param cellStr
 *				The cell string.
 * @param terrain
 *				The automaton terrain.
 * @param state
 *				The state to set the cell to.
 * @thorws InvlaidInitialValueException
 *				If the cell string is missing a comma between x and y values.
 */
void Initial::addCellFromCellStr(string &cellStr, Range *terrain, State state)
{
	int xStart = terrain->getXStart();
	int xEnd = terrain->getXEnd();
	int yStart = terrain->getYStart();
	int yEnd = terrain->getYEnd();

	int comma = cellStr.find(",");
	if(comma == string::npos)
	{
		cerr << "Cell is not formatted as (x,y): (" << cellStr << ")" << endl;
		throw InvalidInitialValueException;
	}

	int xPos = atoi(cellStr.substr(0, comma).c_str());
	int yPos = atoi(cellStr.substr(comma + 1, cellStr.length()).c_str());
		
	xPos = fitToTerrain(xPos, xStart, xEnd);
	yPos = fitToTerrain(yPos, yStart, yEnd);
	if(!contains(xPos, yPos)) //if the cell is not already in the cell vector, add it
	{
		Cell cell(xPos, yPos, state);
		cells.push_back(cell);
	}
}
