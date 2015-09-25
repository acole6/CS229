#ifndef ELEMENTARYCOLORS_H
#define ELEMENTARYCOLORS_H

#include "colors.h"

/**
 * class that stores data for Elementary automaton colors
 * @author Alex Cole
 */
class ElementaryColors : public Colors
{
    /**
     * RGB one color
     */
    Color oneCl;

public:
    /**
     * Default constructor. Sets the one color
     * with all 0 values.
     */
    ElementaryColors();

    /**
     * Constructs with a string representation of
     * an elementary colors struct.
     * @param elementaryColorStruct
     *              The string elementary colors struct.
     */
    ElementaryColors(string elementaryColorStruct);

    /**
     * Constructs with given color values.
     * @param oneCl
     *              The one color.
     * @param defaultCl
     *              The default color.
     */
    ElementaryColors(Color oneCl, Color defaultCl);

    /**
     * Copy constructor.
     * @param elementaryColors
     *              The elementary automaton colors to be copied.
     */
    ElementaryColors(const ElementaryColors &elementaryColors);

    /**
     * Destructor
     */
    virtual ~ElementaryColors();

    /**
     * Overloaded assignment operator.
     * @param elementaryColors
     *              The elementary automaton colors to be copied
     * @return
     *              A copy of elementary automaton colors.
     */
    ElementaryColors& operator=(const ElementaryColors &elementaryColors);

    /**
     * Gets the one color.
     * @return
     *              A pointer to one color.
     */
    Color* getOneColor();

    /**
     * Creates a string colors struct in the form of Colors = { One = oneCl; Zero = defaultCl; };
     * @return
     *              A string representation of elementary colors struct.
     */
    string toString();

private:
    /**
     * Initializes the elementary colors to the given RGB colors
     * @param oneCl
     *              The one RGB color.
     * @param defaultCl
     *              The default RGB color.
     */
    void init(Color oneCl, Color defaultCl);
};

#endif
