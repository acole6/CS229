#ifndef LIFECOLORS_H
#define LIFECOLORS_H

#include "colors.h"

/**
 * class that stores data for life-like automaton colors
 * @author Alex Cole
 */
class LifeColors : public Colors
{
    /**
     * RGB alive color
     */
    Color aliveCl;

public:
    /**
     * Default constructor. Sets alive to color with all 0 values.
     */
    LifeColors();

    /**
     * Takes in a string representation of a like-like colors struct
     * and sets the values of alive and default
     * @param brianColorStruct
     *              The string brian colors struct
     */
    LifeColors(string lifeColorStruct);

    /**
     * Constructs like-like colors with the given colors
     * @param aliveCl
     *              The ready RGB color.
     * @param defaultCl
     *              The default RGB color.
     */
    LifeColors(Color aliveCl, Color defaultCl);

    /**
     * Copy constructor.
     * @param lifeColors
     *              The life-like colors to be copied.
     */
    LifeColors(const LifeColors &lifeColors);

    /**
     * Destructor
     */
    virtual ~LifeColors();

    /**
     * Overloaded assignment operator.
     * @param lifeColors
     *              The life-like colors to be copied.
     * @return
     *              A copy of given life-like colors.
     */
    LifeColors& operator=(const LifeColors &lifeColors);

    /**
     * Gets the alive color.
     * @return
     *              A pointer to the alive color.
     */
    Color* getAliveColor();

    /**
     * Creates a string life-like colors struct in the form of Colors = { Alive = aliveCl; Dead = defaultCl; };
     * @return
     *              A string representation of life-like colors struct.
     */
    string toString();

private:
    /**
     * Initializes the life-like colors to the given RGB colors
     * @param aliveCl
     *              The ready RGB color.
     * @param defaultCl
     *              The default RGB color.
     */
    void init(Color aliveCl, Color defaultCl);
};

#endif
