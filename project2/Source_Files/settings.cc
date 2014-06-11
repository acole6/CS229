#include "settings.h"
#include <stdlib.h>
#include "string.h"
#include <iostream>
#include <fstream>

/**
* @author Alex Cole
* Implementation of setting.h
*/

/**
 * Default constructor that sets the values to default values.
 */
Settings::Settings()
{
	help = false;
	textOutput = false;
	control = false;
	generations = 0;
	gridSize = 10;
	tx = "";
	ty = "";
	wx = "";
	wy = "";
	inFile = "";
	input = "";
}

/**
 * Constructor that initializes the settings based on an array of agruments.
 * @param argc 
 *			The number of arguments.
 * @pram argv 
 *			The array of arguments.
 */
Settings::Settings(int argc, char *argv[])
{
	init(argc, argv);
}

/**
 * Destructor
 */
Settings::~Settings() {}
		
/**
 * Initializes the settings with the given array of arguments.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 */
void Settings::init(int argc, char *argv[])
{
	setFile(argc, argv);
	setHelp(argc, argv);
	setControl(argc, argv);
	setOutput(argc, argv);
	setGenerations(argc, argv);
	setGridSize(argc, argv);
	tx = setRange(argc, argv, "-tx");
	ty = setRange(argc, argv, "-ty");
	wx = setRange(argc, argv, "-wx");
	wy = setRange(argc, argv, "-wy");
}

/**
 * Gets the help flag setting.
 * @return 
 *			True if set otherwise false.
 */
bool Settings::helpFlag()
{
	return help;
}

/**
 * Gets the control flag setting.
 * @return
 *			True if set otherwise false.
 */
bool Settings::controlFlag()
{
	return control;
}

/**
 * Gets the file format setting.
 * @return 
 *			True if -f given otherwise false
 */
bool Settings::fileFormat()
{
	return textOutput;
}

/**
 * Gets the number of generations.
 * @return 
 *			0 by default otherwise the number -g was set to.
 */
int Settings::getGenerations()
{
	return generations;
}

/**
 * Gets the grid size.
 * @return 
 *			10 by default other the number -s was set to
 */
int Settings::getGridSize()
{
	return gridSize;
}

/**
 * Gets the terrain x range.
 * @return 
 *			String representation of the terrain x range.
 */
string Settings::getTX()
{
	return tx;
}

/**
 * Gets the terrain y range.
 * @return 
 *			String representation of the terrain y range.
 */
string Settings::getTY()
{
	return ty;
}

/**
 * Gets the window x range.
 * @return 
 *			String representation of the window x range.
 */
string Settings::getWX()
{
	return wx;
}

/**
 * Gets the window y range
 * @return 
 *			String representation of the window y range.
 */
string Settings::getWY()
{
	return wy;
}
		

/**
 * Gets the name of the file.
 * @return 
 *			The name of the file.
 */
string Settings::getInFile()
{
	return inFile;
}

/**
 * Gets the content of the file.
 * @return 
 *			The contents of the file.
 */
string Settings::getInput()
{
	return input;
}

/**
 * Removes whitesapce and comments from the contents of the file.
 * @param in 
 *			The stream to read from.
 * @return 
 *			0 if file read successfully otherwise -1.
 */
int Settings::stripWhitespaceAndComments(istream& in)
{
	if(!in.good()) { return -1; }

	string line = "";
	while(!in.eof())
	{
		unsigned int i = 0;
		getline(in, line);
		line = trimLeft(line);
		if(line[0] != '#' && i != line.length()) //removes whitespace and comments unless section is quoted and not in a comment
		{
			bool quote = false;
			while(i < line.length())
			{
				if((line[i] == ' ' || line[i] == '\t' || line[i] == '\r') && !quote)
				{
					if ((i + 1) == line.length())
					{
						line = line.substr(0, i);
					}
					else
					{
						line = line.substr(0, i) + line.substr(i + 1, line.length());
					}
				}
				else if(line[i] == '\"' && !quote)
				{
					quote = true;
					i++;
				}
				else if(line[i] == '\"' && quote)
				{
					quote = false;
					i++;
				}
				else if(line[i] == '#' && !quote)
				{
					line = line.substr(0, i);
					break;
				}
				else
				{
					i++;
				}
			}
			input.append(line);
		}
	}
	return 0;
}

/**
 * Set the file if a valid file is given in the arguments.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 */
void Settings::setFile(int argc, char *argv[])
{
	for(int i = 1; i < argc; i++)
	{
		ifstream in(argv[i]);
		if(in.is_open())
		{
			inFile = argv[i];
			in.close();
			break;
		}
	}
}

/**
 * Set the help value if -h was given.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 */
void Settings::setHelp(int argc, char *argv[])
{	
	if(flagPos(argc, argv, "-h") != -1) help = true;
}

/**
 * Set the control value if -c was given.
 * @param argc
 *			The number of arguments.
 * @param argv
 *			The array of arguments.
 */
void Settings::setControl(int argc, char *argv[])
{
	if(flagPos(argc, argv, "-c") != -1) control = true;
}

/**
 * Set the output format if either -f or -v were given.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 */
void Settings::setOutput(int argc, char *argv[])
{
	int fileOutput = flagPos(argc, argv, "-f");
	int visualOutput = flagPos(argc, argv, "-v");
	textOutput = fileOutput > visualOutput  ? true : false;
}

/**
 * Set the number of generations if -g was given.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 * @throws InvalidArgumentException
 *			If value of generation is less than 0.
 */
void Settings::setGenerations(int argc, char *argv[])
{
	int pos = flagPos(argc, argv, "-g");
	generations = pos != -1 && pos + 1 < argc ? atoi(argv[pos + 1]) : 0;
	if(generations < 0)
	{
		cerr << "Generation cannot be a value less than 0: " << generations << endl;
		throw InvalidArgumentException;
	}
}

/**
 * Sets the grid size if -s was given.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 * @throws InvalidArgumentException
 *			If value of grid size is less than 1.
 */
void Settings::setGridSize(int argc, char *argv[])
{
	int pos = flagPos(argc, argv, "-s");
	gridSize = pos != -1 && pos + 1 < argc ? atoi(argv[pos + 1]) : 10;
	if(gridSize < 1) 
	{ 
		cerr << "Grid size cannot be less than 1: " << gridSize << endl;
		throw InvalidArgumentException;
	}
}

/**
 * Gets a range string if the flag was given.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 * @param flag 
 *			The range flag.
 * @return 
 *			The string of the range.
 */
string Settings::setRange(int argc, char *argv[], const char *flag)
{
	int pos = flagPos(argc, argv, flag);
	return pos != -1 && pos + 1 ? argv[pos + 1] : "";
}

/**
 * Gets the position of a flag.
 * @param argc 
 *			The number of arguments.
 * @param argv 
 *			The array of arguments.
 * @param flag 
 *			The flag to get the position of.
 * @return 
 *			The position of the given flag.
 */
int Settings::flagPos(int argc, char *argv[], const char *flag)
{
	int pos = -1;
	for(int i = 1; i < argc; i++)
	{
		if(0 == strcmp(argv[i], flag))
		{
			pos = i;
		}
	}
	return pos;
}

/**
 * Removes whitespace from the left of a string.
 * @param str 
 *			The string to remove the whitesapce.
 * @return 
 *			A string with the whitespace on the left removed.
 */
string Settings::trimLeft(string str)
{
	unsigned int i = 0;
	while(i < str.length() && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
	{
		i++;
	}
	return str.substr(i, str.length());
}
