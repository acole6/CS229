#include "world.h"
#include <sstream>
#include <iostream>

/**
 * Implementation of world.h
 * @author Alex Cole
 */

/**
 * Default constructor that sets initial values to defaults
 */
World::World()
{
	automaton = NULL;
	rows = 0;
	columns = 0;
}

/**
 * Constructor that takes in an automaton to create the world.
 * @param automaton
 *			The automaton used to created the world.
 */
World::World(CellularAutomaton *automaton)
{
	this->automaton = automaton;
	this->rows = (automaton->getTerrain()->getYEnd() - automaton->getTerrain()->getYStart()) + 1;
	this->columns = (automaton->getTerrain()->getXEnd() - automaton->getTerrain()->getXStart()) + 1;
	terrainCellsToWorldCells();
	reset();
}

/**
 * Destructor that does not delete the automaton because
 * a copy of the automaton should not be made by world or
 * passed into world.
 */
World::~World() {}

/**
 * Copy constructor.
 * @param world
 *			The world object that is to be copied.
 */
World::World(const World &world)
{
	automaton = world.automaton;
	currentWorld = world.currentWorld;
	changedCells = world.changedCells;
	rows = world.rows;
	columns = world.columns;
}

/**
 * Overloaded assignment operator.
 * @param world
 *			The world object that is to be copied.
 * @return
 *			A copy of the given world object.
 */
World& World::operator=(const World &world)
{
	if(this == &world) return *this;
	automaton = world.automaton;
	currentWorld = world.currentWorld;
	changedCells = world.changedCells;
	rows = world.rows;
	columns = world.columns;
	return *this;
}

/**
 * Simulates a cellular automaton based on the given number of generations.
 * @param numGenerations
 *			The number of generations to simulate.
 */
void World::simulate(int numGenerations)
{
	Initial *initial = automaton->getInitial();
	for(int i = 0; i < numGenerations; i++)
	{
		if(changedCells.size() == 0) //if no cells have changed, they will continue to not change, so exit.
		{
			initial->convertToTerrainCells(getNonDefaultCells(), automaton->getTerrain());
			return; 
		}

		changedCells.clear();
		for(int row = 0; row < rows; row++)
		{
			for(int col = 0; col < columns; col++)
			{	
				State state = automaton->nextCellState(currentWorld, currentWorld[row][col]);
				if(state != currentWorld[row][col].getState())
				{
					Cell cell(row, col, state);
					changedCells.push_back(cell);
				}
			}
		}
		updateWorld();
	}

	//updates automaton so that current state of automaton can be printed if needed
	initial->convertToTerrainCells(getNonDefaultCells(), automaton->getTerrain());
}



/**
 * Gets the world grid based on the terrain specified in the automaton.
 * @return 
 *			A vector of cell vectors that represents the grid of the world.
 */
vector<vector<Cell>> World::getWorld()
{
	return currentWorld;
}

/**
 * Creates a world grid based on the window specified in the automaton.
 * @return 
 *			A vector of cell vectors that represents the window view of the world.
 */
vector<vector<Cell>> World::generateWindowWorld()
{
	int winYStart = automaton->getWindow()->getYStart();
	int winYEnd = automaton->getWindow()->getYEnd();
	int winXStart = automaton->getWindow()->getXStart();
	int winXEnd = automaton->getWindow()->getXEnd();

	//creates a window world to make it easy to print later
	int winRows = (winYEnd - winYStart) + 1;
	int winCols = (winXEnd - winXStart) + 1;
	vector<vector<Cell>> windowWorld = createWorld(winRows, winCols);

	//find what position in the world terrain to start filling in window world
	int terYEnd = automaton->getTerrain()->getYEnd();
	int terXStart = automaton->getTerrain()->getXStart();
	int topDiff = winYEnd - terYEnd;
	int leftDiff = terXStart - winXStart;

	int topRow = setStartPos(topDiff, rows);
	int leftCol = setStartPos(leftDiff, columns);
	fillWindowWorld(windowWorld, topRow, leftCol);

	return windowWorld;
}

/**
 * Gets the number of rows for the world grid.
 * @return 
 *			The number of rows.
 */
int World::getRows()
{
	return rows;
}
		
/**
 * Gets the columns of the world.
 * @return 
 *			The number of columns.
 */
int World::getCols()
{
	return columns;
}

/**
 * Gets the current automaton which may have been modified if simulate had been called
 * @return 
 *			A pointer to world's automaton
 */
CellularAutomaton* World::getAutomaton()
{
	return automaton;
}

/**
 * String representation of the world grid. If the world's automaton has a window ranges, 
 * the window view of the world will be generated. Otherwise the terrain view of the world
 * will be generated
 * @return 
 *			String representation of the terrain view of the world or window view of the world
 */
string World::toString()
{
	if(automaton->getWindow() == NULL) //if NULL, then print terrain world
	{
		return toStringWorld(currentWorld);
	}
	else //otherwise print window world
	{
		return toStringWindow();
	}
}

/**
 * Converts the world grid from a cell grid to a Color grid based based on the colors specified
 * in the automaton. If the automaton has a window range, the window grid will be returned otherwise
 * the grid based on the terrain will be returned.
 * @return
 *			A color grid of the terrain of the world or the window of the world
 */
vector<vector<Color>> World::toColor()
{
	if(automaton->getWindow() == NULL) //behaves similar to toString()
	{
		return toColorWorld(currentWorld);
	}
	else
	{
		return toColorWindow();
	}
}

/**
 * Resets the world back to the initial state when the world was first created.
 */
void World::reset()
{
	changedCells = initialCells;
	currentWorld = createWorld(rows, columns);
	updateWorld();
}

/**
 * Converts the initial terrain cell positions to grid friendly positions.
 */
void World::terrainCellsToWorldCells()
{
	vector<Cell> terrainCells = automaton->getInitial()->getCells();
	int yStart = automaton->getTerrain()->getYStart();
	int yEnd = automaton->getTerrain()->getYEnd();
	int xStart = automaton->getTerrain()->getXStart();
	int xEnd = automaton->getTerrain()->getXEnd();
	for(int i = 0; i < automaton->getInitial()->size(); i++)
	{
		int tRow = terrainCells[i].getY();
		int tCol = terrainCells[i].getX();
		if(tRow >= yStart && tRow <= yEnd && tCol >= xStart && tCol <= xEnd) //makes sure value is in terrain first
		{
			int row = yEnd <= 0 ? (yEnd * -1) + tRow : tRow - yEnd; //converts y terrain to row
			if(row < 0) { row = row * -1; }
			int col = xStart <= 0 ? (xStart * -1) + tCol : tCol - xStart; //conerts x terrain to col
		
			Cell cell(row, col, terrainCells[i].getState());
			initialCells.push_back(cell);
		}
	}
}

/**
 * Updates the world grid based on the cells that have changed between generations.
 */
void World::updateWorld()
{
	for(unsigned int i = 0; i < changedCells.size(); i++)
	{
		int row = changedCells[i].getX();
		int col = changedCells[i].getY();
		currentWorld[row][col].setState(changedCells[i].getState());
	}
}

/**
 * Creates a string version of the window view of the world.
 * @return 
 *			The string representation of the window view of the world.
 */
string World::toStringWindow()
{
	return toStringWorld(generateWindowWorld());
}

/**
 * Creates a color grid based on the window view of the world.
 * @return
 *			A vector of color vectors that represent the window view of the world.
 */
vector<vector<Color>> World::toColorWindow()
{
	return toColorWorld(generateWindowWorld());
}

/**
 * Creates a world with the given rows and columns and sets all states to default.
 * @param rows 
 *			The number of rows.
 * @param columns 
 *			The number of columns.
 * @return 
 *			The world as a vector of cell vectors with all cells set to default
 */
vector<vector<Cell>> World::createWorld(int rows, int columns)
{
	vector<vector<Cell>> ret;
	for(int row = 0; row < rows; row++)
	{
		ret.push_back(vector<Cell>(columns));
		for(int col = 0; col < columns; col++)
		{
			ret[row][col].setX(row);
			ret[row][col].setY(col);
		}
	}
	return ret;
}

/**
 * Converts a given world to a string representation of the world.
 * @param world
 *			The world to convert into a string.
 * @return 
 *			A string representation of given world.
 */
string World::toStringWorld(vector<vector<Cell>> world)
{
	string ret = "";
	for(unsigned int row = 0; row < world.size(); row++)
	{
		for(unsigned int col = 0; col < world[0].size(); col++)
		{
			char ch = automaton->getChar(world[row][col]);
			ret += ch;
		}
		ret += "\n";
	}
	return ret;
}

/**
 * Converts a given world to a color representation of the world.
 * @param world
 *			The world to convert into a color world.
 * @return
 *			A vector of color vectors that represents a color version of the world.
 */
vector<vector<Color>> World::toColorWorld(vector<vector<Cell>> world)
{
	vector<vector<Color>> ret;
	for(unsigned int row = 0; row < world.size(); row++)
	{
		ret.push_back(vector<Color>(world[row].size()));
		for(unsigned int col = 0; col < world[row].size(); col++)
		{
			Color color = automaton->getColor(world[row][col]);
			ret[row][col].setRed(color.getRed());
			ret[row][col].setGreen(color.getGreen());
			ret[row][col].setBlue(color.getBlue());
		}
	}
	return ret;
}

/**
 * Sets position to start in the terrain.
 * @param diff 
 *			The difference between window and terrain range.
 * @param length 
 *			The length of the terrain range.
 * @return 
 *			The position in the terrain to start.
 */
int World::setStartPos(int diff, int length)
{
	int ret = 0;
	if(diff > 0) //if positive, need to to shift left from end of row/col
	{
		ret = length - (diff % length);
		if(ret == length)
		{
			ret = 0;
		}
	}
	else if(diff < 0) //if negative, need to shift right from beginning of row/col
	{
		diff = diff * -1;
		ret = diff % length;
	}
	return ret;
}

/**
 * Fills the window world with values from the terrain based on terrain starting positions.
 * @param windowWorld 
 *			The window view of the world.
 * @param rowStart 
 *			The row to start at in the terrain.
 * @param colStart 
 *			The column to start at in the terrain.
 */
void World::fillWindowWorld(vector<vector<Cell>> &windowWorld, int rowStart, int colStart)
{
	int row = rowStart;
	for(unsigned int winRow = 0; winRow < windowWorld.size(); winRow++) //go through window world
	{
		int col = colStart; //need to reset back to colstart value
		for(unsigned int winCol = 0; winCol < windowWorld[0].size(); winCol++)
		{
			State state = currentWorld[row][col].getState();
			if(state != State::DEFAULT)
			{
				windowWorld[winRow][winCol].setState(state);
			}
			col++;
			if(col > columns - 1) //if this is true, terrain world column needs to be set back to 0
			{
				col = 0;
			}
		}
		row++;
		if(row > rows - 1 && winRow == 0) //if still on the first window row, the row value needs to be reset to rowstart
		{
			row = rowStart;
		}
		else if(row > rows -1) //otherwise if exceeding terrain world, row reset to 0
		{
			row = 0;
		}
	}
}

/**
 * Gets the cells in the world that are not in the default state.
 * @return
 *			A cell vector of cells not in the default state.
 */
vector<Cell> World::getNonDefaultCells()
{
	vector<Cell> ret;
	for(unsigned int row = 0; row < rows; row++)
	{
		for(unsigned int col = 0; col < columns; col++)
		{ 
			State state = currentWorld[row][col].getState();
			if(state != State::DEFAULT)
			{
				int x = currentWorld[row][col].getX();
				int y = currentWorld[row][col].getY();
				Cell cell(x, y, state);
				ret.push_back(cell);
			}
		}
	}
	return ret;
}
