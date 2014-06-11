#include <iostream>
#include <fstream>
#include "settings.h"
#include "lifeclass.h"
#include "elementary.h"
#include "brian.h"
#include "world.h"
#include "automatonparser.h"

/**
 * life program that displays cellular automaton as a file or ascii grid
 * @author Alex Cole
 */
int main(int argc, char* argv[])
{
	Settings settings;
	if(argc > 1) 
	{ 
		try
		{
			settings.init(argc, argv);
		}
		catch(int e)
		{
			if(e == InvalidArgumentException) return -1;
		}
	}
	
	if(settings.helpFlag())
	{
		cout << "\nlife represents a game of life for a cellular automaton in either an ascii grid or in life file format based on the number of generations that have passed.\n";
		cout << "Supported automaton: Life-like, Elementary, and Brian's Brain.\n";
		cout << "Supported switches:\n-g n specifies the desired generation number. n is 0 by default\n";
		cout << "-f Sends output to cout or standard out in the same format as input file.\n -h displays the help menu.\n";
		cout << "-tx l..h sets the x range for the terrain in the format of low to high (low..high), which overrides the terrain values in input.\n";
		cout << "-ty l..h sets the y range for the terrain in the format of low to high (low..high), which overrides the terrain values in input.\n";
		cout << "-v Sends output to cout or standard out in the format of an ascii grid\n";
		cout << "-wx l..h sets the x range for the window in the format of low to high (low..high), which overrides the window values in input.\n";
		cout << "-wy l..h sets the y range for the window in the format of low to high (low..high), which overrides the window values in input.\n\n";
		cout << "Window values whether given in input on or command line with take precedence over terrain values when world is displayed as ascii characters.\n";
		cout << "By default output is in the form of -v flag and a name is not required for input. If initial struct is not specified, then all cells will be set to dead.\n";
		return 0;
	}

	if(settings.getInFile().empty()) //no file specified, then read from cin
	{
		if(settings.stripWhitespaceAndComments(cin) != 0)
		{
			cerr << "problem reading from standard input\n";
			return -1;
		}
	}
	else
	{
		ifstream in(settings.getInFile());
		if(settings.stripWhitespaceAndComments(in) != 0)
		{
			cerr << "problem reading from file: " << settings.getInFile() << "\n";
			return -1;
		}
		in.close();
	}

	CellularAutomaton *automaton = NULL;
	World *world = NULL;
	try
	{
		map<string, string> automatonStruct = AutomatonParser::parse(settings.getInput());
		if(!automatonStruct["Life"].empty())
		{
			automaton = new Life(automatonStruct["Life"]);
		}
		else if(!automatonStruct["Elementary"].empty())
		{
			automaton = new Elementary(automatonStruct["Elementary"]);
		}
		else if(!automatonStruct["Brian"].empty())
		{
			automaton = new Brian(automatonStruct["Brian"]);
		}
		else
		{
			cerr << "File does not contain valid cellular automaton: " << settings.getInFile() << endl;
			return -1;
		}
		automaton->updateTerrain(settings.getTX(), settings.getTY());
		automaton->updateWindow(settings.getWX(), settings.getWY());
		world = new World(automaton);
		world->simulate(settings.getGenerations());
	}
	catch(int e)
	{
		if(e == InvalidFileFormatException)
		{
			cerr << "File is not in valid life file format: " << settings.getInFile() << endl;
		}
		delete automaton;
		delete world;
		return -1;
	}

	if(settings.fileFormat())
	{
		cout << world->getAutomaton()->toString(); //-f
	}
	else
	{
		cout << world->toString(); //-v or if no flag specified
	}
	cout << endl;

	delete automaton;
	delete world;
 	return 0;
}
