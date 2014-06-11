#include "automatonparser.h"
#include <iostream>

/**
 * implementation of automatonparser.h
 * @author Alex Cole
 */

/**
 * Default constructor.
 */
AutomatonParser::AutomatonParser() {}

/**
 * Destructor.
 */
AutomatonParser::~AutomatonParser() {}

/**
 * Parses automaton file into key-value pairs. The key is the
 * identifier and the value could be a struct or other value specified after
 * the identifier.
 * @param input 
 *				The automaton file with all comments and whitespace removed.
 * @return 
 *				A map of key-value pairs.
 * @throws InvalidFileFormatException 
 *				If the file is not properly formatted.
 */
map<string, string> AutomatonParser::parse(string input)
{
	map<string, string> data;
	int keyBeginIndex = -1;
	int keyEndIndex = -1;
	int valueBeginIndex = -1;
	int valueEndIndex = -1;
	string key = "";
	string value = "";
	
	if(!properFormat(input)) throw InvalidFileFormatException; 

	input = removeChar(input, '{', '}'); //removes struct brackets if there

	while(hasKey(input))
	{
		keyBeginIndex = 0;
		keyEndIndex = input.find("=");
		key = input.substr(keyBeginIndex, keyEndIndex - keyBeginIndex);
		
		valueBeginIndex = keyEndIndex + 1;
		valueEndIndex = findMatchingCharPos(input, '=', ';');
		value = input.substr(valueBeginIndex, valueEndIndex - valueBeginIndex);
		value = removeChar(value, '\"', '\"'); //removes surrounding quotes if there

		data[key] = value;
		input = input.substr(valueEndIndex + 1, input.length()); //removes what has already been checked
	}
	return data;
}

/**
 * Gets the value from the map based on the key identifier.
 * @param map
 *				The map of key-value pairs.
 * @param identifier
 *				The key identifier.
 * @param checkValue
 *				If the value of the identifier should be checked. Default is false.
 * @return
 *				The value of the key-value pair based on the given identifier.
 * @throws MissingIdentifierException
 *				If the given key identifier is not in the map.
 * @throws IdentifierHasNoValueException
 *				If checkValue is true and the key identifier does not have a value.
 */
string AutomatonParser::getValue(map<string, string> &map, string identifier, bool checkValue)
{
	if(map.find(identifier) == map.end())
	{
		cerr << "Missing identifier: " << identifier << endl;
		throw MissingIdentifierException;
	}
	string value = map[identifier];
	if(checkValue && value.empty())
	{
		cerr << "Identifier is not assigned a value: " << identifier << endl;
		throw IdentifierHasNoValueException;
	}
	return value;
}

/**
 * Checks to see if the input has a key.
 * @param input 
 *				The string input.
 * @return 
 *				True if there is a key otherwise false.
 */
bool AutomatonParser::hasKey(string input)
{
	return input.find("=") != string::npos;
}

/**
 * Checks to see if the value is in correct automaton file format.
 * @param str 
 *				The portion of the automaton file to be checked.
 * @return 
 *				True if in proper format otherwise false.
 */
bool AutomatonParser::properFormat(string str)
{
	string temp = removeQuotedStr(str); //remove quoted strings before checking format

	//count how many starting char values there are and create arrays to store their position
	int lBraceSize = countChar(temp, '{');
	int equalSize = countChar(temp, '=');
	int *lBraces = new int[lBraceSize];
	int *equals = new int[equalSize];

	//matches the starting characters with their terminating characters
	bool validBraces = checkFormat(lBraces, lBraceSize, temp, '{', '}');
	bool validAssignStmts = checkFormat(equals, equalSize, temp, '=', ';');

	delete[] lBraces;
	delete[] equals;

	return validBraces && validAssignStmts; //if both are valid, the file is in valid format
}

/**
 * Counts the number of characters in a string.
 * @param str 
 *				The string that the characters are going to be counted.
 * @param ch 
 *				The character to count.
 * @return 
 *				The number of the given character in the string.
 */
int AutomatonParser::countChar(string str, char ch)
{
	int count = 0;
	for(unsigned int i = 0; i < str.length(); i++)
	{
		if(str[i] == ch) { count++; }
	}
	return count;
}

/**
 * Checks to see if file has a terminating character for each initial character.
 * @param arr 
 *				The positions of the initial characters.
 * @param length 
 *				The length of the array.
 * @param str 
 *				The string that the format needs to be checked.
 * @param start 
 *				The initial character.
 * @param end 
 *				The terminating character.
 * @return 
 *				True if in correct format otherwise false.
 */
bool AutomatonParser::checkFormat(int *arr, int length, string str, char start, char end)
{
	int arrPos = -1;
	for(unsigned int i = 0; i < str.length(); i++)
	{
		if(str[i] == start) //if char is the starting char, add position to the array
		{
			arrPos++;
			arr[arrPos] = i;
		}
		else if(str[i] == end) //if terminating char appears before a starting char, invalid format
		{
			if(arrPos == -1)
			{
				return false;
			}

			int pos = findMatchingCharPos(arr, arrPos + 1); //find the terminating char position
			if(pos != -1) //if found set starting position to -1
			{
				arr[pos] = -1;
			}
			else //otherwise invalid format
			{
				return false;
			}
		}
	}
	return findMatchingCharPos(arr, length) < 0; //if all start chars were matched with terminating chars, then valid format
}

/**
 * Finds the terminating character to the given start character.
 * @param str 
 *				The string to be checked.
 * @param start 
 *				The starting character.
 * @param end 
 *				The terminating character.
 * @return 
 *				The position of the terminating character otherwise -1.
 */
int AutomatonParser::findMatchingCharPos(string str, char start, char end)
{
	int count = 0;
	bool found = false;
	for(unsigned int i = 0; i < str.length(); i++)
	{
		if(str[i] == start && !found) //if the starting char and it has not been found previously, increase the count and set found to true
		{
			count++;
			found = true;
		}
		else if(str[i] == start) //if the starting char, increase the count
		{
			count++;
		}
		else if(str[i] == end && found)//if the terminating char and the starting char has been found, then decrease the count
		{
			count--;
			if(count == 0) { return i; } //if the count has been reduced to 0, then this is the matching position, so return it 
		}
	}
	return -1; //matching position was not found
}

/**
 * Finds the starting character position in the array for a terminating character.
 * @param arr 
 *				An array of starting positions.
 * @param length 
 *				The length of the array.
 * @return 
 *				The position of the corresponding start character otherwise -1.
 */
int AutomatonParser::findMatchingCharPos(int *arr, int length)
{
	for(int i = length - 1; i >= 0; i--) //looks through array in reverse until it finds a positive value, then returns that position
	{
		if(arr[i] >= 0) { return i; }
	}
	return -1; //no positive values found in the array
}

/**
 * Removes a quoted string from the string.
 * @param str 
 *				The string to have the quote removed from.
 * @return 
 *				A string with no quoted strings in it.
 */
string AutomatonParser::removeQuotedStr(string str)
{
	while(str.find('\"') != string::npos) //checks for quote in the string
	{
		int leftQuote = -1;
		int rightQuote = -1;
		for(unsigned int i = 0; i < str.length(); i++)
		{
			if(str[i] == '\"' && leftQuote == -1) //finds left quote
			{
				leftQuote = i;
			}
			else if(str[i] == '\"') //finds right quote
			{
				rightQuote = i; 
				break;
			}
		}

		if(leftQuote != -1 && rightQuote == -1) { return ""; } //returns empty string if left quote but no right quote. Invalid format

		string left = str.substr(0, leftQuote);
		string right = str.substr(rightQuote + 1, str.length());

		str = left + right;
	}
	return str;
}

/**
 * Removes starting and terminating characters from a string.
 * @param str 
 *				The string to have the characters removed.
 * @param start 
 *				The start character to be removed.
 * @param end 
 *				The end character to be removed.
 * @return 
 *				The string with the starting and terminating characters removed.
 */
string AutomatonParser::removeChar(string str, char start, char end)
{
	int lastPos = str.length() - 1;
	if(str[0] == start && str[lastPos] == end) //if the first character matches start and last matches end, remove them
	{
		return str.substr(1, lastPos - 1);
	}
	else
	{
		return str;
	}
}
