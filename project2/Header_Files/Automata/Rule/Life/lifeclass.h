#ifndef LIFECLASS_H
#define LIFECLASS_H

#include "ruleautomaton.h"

/**
 * class that represents Life-like cellular automaton
 * @author Alex Cole
 */
class Life : public RuleAutomaton
{
private:
    /**
     * number of neighbors in alive state needed to be born
     */
    vector<int> born;

    /**
     * number of neighbors in alive state needed to stay alive
     */
    vector<int> stayAlive;

public:
    /**
    * Default constructor that sets values
    * to NULL and the name to an empty string.
    */
    Life();

    /**
    * Takes in a string life-like automaton struct and sets the values to
    * the values in the struct
    * @param lifeStruct
    *               The string life-like automaton struct
    */
    Life(string lifeStruct);

    /**
     * Copy constructor.
     * @param life
     *              The like-like automaton to be copied.
     */
    Life(const Life &life);

    /**
     * Destructor
     */
    virtual ~Life();

    /**
     * Overloaded assignment operator.
     * @param life
     *               The life-like automaton to be copied.
     * @return
     *              A copy of the life-like automaton.
     */
    Life& operator=(const Life &life);

    /**
     * Determines the next state of a given cell based on the world
     * and neighboring cells.
     * @param world
     *              The grid of cells.
     * @param cell
     *              The cell that the next state needs to be determined.
     * @return
     *              The next state of the cell.
     */
    virtual State nextCellState(vector<vector<Cell>> &world, Cell &cell);

    /**
     * Gets the char representation of the state of the given cell.
     * @param cell
     *              The cell to get the char value of.
     * @return
     *              The char representation of the state of the cell.
     */
    virtual char getChar(Cell &cell);

    /**
     * Gets the color representation of the state of the given cell.
     * @param cell
     *              The cell to get the color value of.
     * @return
     *              The color representation of the state of the cell.
     */
    virtual Color getColor(Cell &cell);

    /**
     * Creates a string in the automaton file format.
     * @return
     *              String representation of automaton file
     */
    virtual string toString();

private:
    /**
     * Adds values to the born int vector based on the rule string.
     * @throws InvalidRuleException
     *              If the rule is not in valid format (B012../S012..)
     */
    void setBorn();

    /**
     * Adds values to the stayAlive int vector based on the rule string.
     * @throws InvalidRuleException
     *              If the rule is not in valid format (B012../S012..)
     */
    void setStayAlive();

    /**
     * Adds digits to int vector from a string of digits.
     * @param digits
     *              The int vector for the digits to be added.
     * @param digitStr
     *              The string of digits.
     * @throws InvalidRuleException
     *              If one of the digits is not in the range 0-8 (inclusive).
     */
    void fillVectorFromDigitStr(vector<int> &digits, string digitStr);

    /**
     * Checks to see if the value is in the born vector.
     * @param count
     *              The value to be checked.
     * @return
     *              True if it is in the vector otherwise false.
     */
    bool isBorn(int count);

    /**
     * Checks to see if the value is in the sayAlive vector.
     * @param count
     *              The value to be checked.
     * @return
     *              True if it is in the vector otherwise false.
     */
    bool staysAlive(int count);

    /**
     * Checks to see if the value is in an int vector.
     * @param nums
     *              The int vector.
     * @param count
     *              The value to be checked.
     * @return
     *              True if it is in the vector otherwise false.
     */
    bool foundCount(vector<int> &nums, int count);
};

#endif
