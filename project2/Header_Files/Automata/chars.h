#ifndef CHARS_H
#define CHARS_H

#include <string>
#include <vector>

using namespace std;

/**
 * abstract class that stores data from char struct
 * @author Alex Cole
 */
class Chars
{
private:
    /**
     * default character
     */
    int defaultCh;

public:
    /**
     * Default constructor that sets default
     * character to 0.
     */
    Chars();

    /**
     * Constructs Chars with the given value.
     * @param defaultCh
     *          The default character value
     */
    Chars(int defaultCh);

    /**
     * Copy constructor.
     * @param chars
     *          The chars to be copied.
     */
    Chars(const Chars &chars);

    /**
     * Destructor
     */
    virtual ~Chars();

    /**
     * Overloaded assignment operator.
     * @param chars
     *          The chars to be copied.
     * @return
     *          A copy of the given chars.
     */
    Chars& operator=(const Chars &chars);

    /**
     * Gets the default character value.
     * @return
     *          The default character value as an int.
     */
    int getDefaultChar() const;

    /**
     * Sets the default character value.
     * @param defaultCh
     *          The value for the default character to be set to.
     */
    void setDefaultChar(int defaultCh);

    /**
     * Not implemented.
     * Creates a string chars struct in the form of Chars = { Default = defaultCh; };
     * @return
     *          A string representation of chars struct.
     */
    virtual string toString() = 0;
};

#endif
