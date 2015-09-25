#ifndef WORLD_H
#define WORLD_H

#include "cellularautomaton.h"

/**
 * Class that represents a world for a cellular automaton.
 * @author Alex Cole
 */
class World
{
private:
    /**
     * The cellular automaton for this world.
     */
    CellularAutomaton *automaton;

    /**
     * The grid of cells for the current state of the world.
     */
    vector<vector<Cell>> currentWorld;

    /**
     * The initial cells passed in by the automaton.
     */
    vector<Cell> initialCells;

    /**
     * The cells that have be changed states between generations.
     */
    vector<Cell> changedCells;

    /**
     * The number of rows in the grid.
     */
    int rows;

    /**
     * The number of columns in the grid.
     */
    int columns;

public:
    /**
     * Default constructor that sets initial values to defaults
     */
    World();

    /**
     * Constructor that takes in an automaton to create the world.
     * @param automaton
     *          The automaton used to created the world.
     */
    World(CellularAutomaton *automaton);

    /**
     * Destructor that does not delete the automaton because
     * a copy of the automaton should not be made by world or
     * passed into world.
     */
    ~World();

    /**
     * Copy constructor.
     * @param world
     *          The world object that is to be copied.
     */
    World(const World &world);

    /**
     * Overloaded assignment operator.
     * @param world
     *          The world object that is to be copied.
     * @return
     *          A copy of the given world object.
     */
    World& operator=(const World &world);

    /**
     * Simulates a cellular automaton based on the given number of generations.
     * @param numGenerations
     *          The number of generations to simulate.
     */
    void simulate(int numGenerations);

    /**
     * Gets the world grid based on the terrain specified in the automaton.
     * @return
     *          A vector of cell vectors that represents the grid of the world.
     */
    vector<vector<Cell>> getWorld();

    /**
     * Creates a world grid based on the window specified in the automaton.
     * @return
     *          A vector of cell vectors that represents the window view of the world.
     */
    vector<vector<Cell>> generateWindowWorld();

    /**
     * Gets the number of rows for the world grid.
     * @return
     *          The number of rows.
     */
    int getRows();

    /**
     * Gets the columns of the world.
     * @return
     *          The number of columns.
     */
    int getCols();

    /**
     * Gets the current automaton which may have been modified if simulate had been called
     * @return
     *          A pointer to world's automaton
     */
    CellularAutomaton* getAutomaton();

    /**
     * String representation of the world grid. If the world's automaton has a window ranges,
     * the window view of the world will be generated. Otherwise the terrain view of the world
     * will be generated
     * @return
     *          String representation of the terrain view of the world or window view of the world
     */
    string toString();

    /**
     * Converts the world grid from a cell grid to a Color grid based based on the colors specified
     * in the automaton. If the automaton has a window range, the window grid will be returned otherwise
     * the grid based on the terrain will be returned.
     * @return
     *          A color grid of the terrain of the world or the window of the world
     */
    vector<vector<Color>> toColor();

    /**
     * Resets the world back to the initial state when the world was first created.
     */
    void reset();

private:
    /**
     * Converts the initial terrain cell positions to grid friendly positions.
     */
    void terrainCellsToWorldCells();

    /**
     * Updates the world grid based on the cells that have changed between generations.
     */
    void updateWorld();

    /**
     * Creates a string version of the window view of the world.
     * @return
     *          The string representation of the window view of the world.
     */
    string toStringWindow();

    /**
     * Creates a color grid based on the window view of the world.
     * @return
     *          A vector of color vectors that represent the window view of the world.
     */
    vector<vector<Color>> toColorWindow();

    /**
     * Creates a world with the given rows and columns and sets all states to default.
     * @param rows
     *          The number of rows.
     * @param columns
     *          The number of columns.
     * @return
     *          The world as a vector of cell vectors with all cells set to default
     */
    vector<vector<Cell>> createWorld(int rows, int columns);

    /**
     * Converts a given world to a string representation of the world.
     * @param world
     *          The world to convert into a string.
     * @return
     *          A string representation of given world.
     */
    string toStringWorld(vector<vector<Cell>> world);

    /**
     * Converts a given world to a color representation of the world.
     * @param world
     *          The world to convert into a color world.
     * @return
     *          A vector of color vectors that represents a color version of the world.
     */
    vector<vector<Color>> toColorWorld(vector<vector<Cell>> world);

    /**
     * Sets position to start in the terrain.
     * @param diff
     *          The difference between window and terrain range.
     * @param length
     *          The length of the terrain range.
     * @return
     *          The position in the terrain to start.
     */
    int setStartPos(int diff, int length);

    /**
     * Fills the window world with values from the terrain based on terrain starting positions.
     * @param windowWorld
     *          The window view of the world.
     * @param rowStart
     *          The row to start at in the terrain.
     * @param colStart
     *          The column to start at in the terrain.
     */
    void fillWindowWorld(vector<vector<Cell>> &windowWorld, int rowStart, int colStart);

    /**
     * Gets the cells in the world that are not in the default state.
     * @return
     *          A cell vector of cells not in the default state.
     */
    vector<Cell> getNonDefaultCells();
};

#endif
