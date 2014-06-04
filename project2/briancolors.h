#ifndef BRIANCOLORS_H
#define BRIANCOLORS_H

#include "colors.h"

/**
 * class that stores data for brian automaton colors
 * @author Alex Cole
 */
class BrianColors : public Colors
{
	/**
	 * RGB ready color
	 */
	Color readyCl;

	/**
	 * RGB firing color
	 */
	Color firingCl;

public:
	/**
	 * Default constructor. Sets ready and firing to colors with all 0 values.
	 */
	BrianColors();

	/**
	 * Takes in a string representation of a brian colors struct
	 * and sets the values of ready, firing and default
	 * @param brianColorStruct 
	 *				The string brian colors struct
	 */
	BrianColors(string brianColorStruct);

	/**
	 * Constructs brian colors with the given colors
	 * @param readyCl 
	 *				The ready RGB color. 
	 * @param firingCl 
	 *				The firing RGB color.
	 * @param defaultCl
	 *				The default RGB color.
	 */
	BrianColors(Color readyCl, Color firingCl, Color defaultCl);

	/**
	 * Copy constructor.
	 * @param brianColors 
	 *				The brian colors to be copied.
	 */
	BrianColors(const BrianColors &brianColors);

	/**
	 * Destructor
	 */
	virtual ~BrianColors();

	/**
	 * Overloaded assignment operator.
	 * @param brianColors 
	 *				The brian colors to be copied.
	 * @return 
	 *				A copy of given brian colors.
	 */
	BrianColors& operator=(const BrianColors &brianColors);

	/**
	 * Gets the ready color.
	 * @return 
	 *				A pointer to the ready color.
	 */
	Color* getReadyColor();
	
	/**
	 * Gets the firing color
	 * @return
	 *				A pointer to the firing color.
	 */
	Color* getFiringColor();

	/**
	 * Creates a string brian colors struct in the form of Colors = { Ready = readyCl; Firing = firingCl; Refactory = defaultCl; };
	 * @return 
	 *				A string representation of brian colors struct.
	 */
	string toString();

private:
	/**
	 * Initializes the brian colors to the given RGB colors
	 * @param readyCl 
	 *				The ready RGB color. 
	 * @param firingCl 
	 *				The firing RGB color.
	 * @param defaultCl
	 *				The default RGB color.
	 */
	void init(Color readyCl, Color firingCl, Color defaultCl);
};

#endif
