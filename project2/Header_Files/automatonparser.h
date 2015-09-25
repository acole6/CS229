#ifndef AUTOMATONPARSER_H
#define AUTOMATONPARSER_H

#include <map>
#include <string>

using namespace std;

const int MissingIdentifierException = 1;
const int InvalidFileFormatException = 2;
const int IdentifierHasNoValueException = 3;

/**
 * Class with static functions to parse an automaton file
 * @author Alex Cole
 */
class AutomatonParser
{
public:
    /**
     * Default constructor.
     */
    AutomatonParser();

    /**
     * Destructor.
     */
    ~AutomatonParser();

    /**
     * Parses automaton file into key-value pairs. The key is the
     * identifier and the value could be a struct or other value specified after
     * the identifier.
     * @param input
     *              The automaton file with all comments and whitespace removed.
     * @return
     *              A map of key-value pairs.
     * @throws InvalidFileFormatException
     *              If the file is not properly formatted.
     */
    static map<string, string> parse(string input);

    /**
     * Gets the value from the map based on the key identifier.
     * @param map
     *              The map of key-value pairs.
     * @param identifier
     *              The key identifier.
     * @param checkValue
     *              If the value of the identifier should be checked. Default is false.
     * @return
     *              The value of the key-value pair based on the given identifier.
     * @throws MissingIdentifierException
     *              If the given key identifier is not in the map.
     * @throws IdentifierHasNoValueException
     *              If checkValue is true and the key identifier does not have a value.
     */
    static string getValue(map<string, string> &map, string identifier, bool checkValue = false);

private:
    /**
     * Checks to see if the input has a key.
     * @param input
     *              The string input.
     * @return
     *              True if there is a key otherwise false.
     */
    static bool hasKey(string input);

    /**
     * Checks to see if the value is in correct automaton file format.
     * @param str
     *              The portion of the automaton file to be checked.
     * @return
     *              True if in proper format otherwise false.
     */
    static bool properFormat(string str);

    /**
     * Counts the number of characters in a string.
     * @param str
     *              The string that the characters are going to be counted.
     * @param ch
     *              The character to count.
     * @return
     *              The number of the given character in the string.
     */
    static int countChar(string str, char ch);

    /**
     * Checks to see if file has a terminating character for each initial character.
     * @param arr
     *              The positions of the initial characters.
     * @param length
     *              The length of the array.
     * @param str
     *              The string that the format needs to be checked.
     * @param start
     *              The initial character.
     * @param end
     *              The terminating character.
     * @return
     *              True if in correct format otherwise false.
     */
    static bool checkFormat(int *arr, int length, string str, char start, char end);

    /**
     * Finds the terminating character to the given start character.
     * @param str
     *              The string to be checked.
     * @param start
     *              The starting character.
     * @param end
     *              The terminating character.
     * @return
     *              The position of the terminating character otherwise -1.
     */
    static int findMatchingCharPos(string str, char start, char end);

    /**
     * Finds the starting character position in the array for a terminating character.
     * @param arr
     *              An array of starting positions.
     * @param length
     *              The length of the array.
     * @return
     *              The position of the corresponding start character otherwise -1.
     */
    static int findMatchingCharPos(int *arr, int length);

    /**
     * Removes a quoted string from the string.
     * @param str
     *              The string to have the quote removed from.
     * @return
     *              A string with no quoted strings in it.
     */
    static string removeQuotedStr(string str);

    /**
     * Removes starting and terminating characters from a string.
     * @param str
     *              The string to have the characters removed.
     * @param start
     *              The start character to be removed.
     * @param end
     *              The end character to be removed.
     * @return
     *              The string with the starting and terminating characters removed.
     */
    static string removeChar(string str, char start, char end);
};

#endif
