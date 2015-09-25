#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

using namespace std;

const int InvalidArgumentException = 7;

/**
 * class that stores the program settings
 * @author Alex Cole
 */
class Settings
{
    /**
     * help switch
     */
    bool help;

    /**
     * output format switch
     */
    bool textOutput;

    /**
     * control dialog switch
     */
    bool control;

    /**
     * generation switch
     */
    int generations;

    /**
     * grid size switch
     */
    int gridSize;

    /**
     * terrain x range switch
     */
    string tx;

    /**
     * terrain y range switch
     */
    string ty;

    /**
     * window x range switch
     */
    string wx;

    /**
     * window y range switch
     */
    string wy;

    /**
     * automaton file
     */
    string inFile;

    /**
     * data in automaton file
     */
    string input;

public:
    /**
     * Default constructor that sets the values to default values.
     */
    Settings();

    /**
     * Constructor that initializes the settings based on an array of arguments.
     * @param argc
     *          The number of arguments.
     * @pram argv
     *          The array of arguments.
     */
    Settings(int argc, char *argv[]);

    /**
     * Destructor
     */
    ~Settings();

    /**
     * Initializes the settings with the given array of arguments.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     */
    void init(int argc, char *argv[]);

    /**
     * Gets the help flag setting.
     * @return
     *          True if set otherwise false.
     */
    bool helpFlag();

    /**
     * Gets the control flag setting.
     * @return
     *          True if set otherwise false.
     */
    bool controlFlag();

    /**
     * Gets the file format setting.
     * @return
     *          True if -f given otherwise false
     */
    bool fileFormat();

    /**
     * Gets the number of generations.
     * @return
     *          0 by default otherwise the number -g was set to.
     */
    int getGenerations();

    /**
     * Gets the grid size.
     * @return
     *          10 by default other the number -s was set to
     */
    int getGridSize();

    /**
     * Gets the terrain x range.
     * @return
     *          String representation of the terrain x range.
     */
    string getTX();

    /**
     * Gets the terrain y range.
     * @return
     *          String representation of the terrain y range.
     */
    string getTY();

    /**
     * Gets the window x range.
     * @return
     *          String representation of the window x range.
     */
    string getWX();

    /**
     * Gets the window y range
     * @return
     *          String representation of the window y range.
     */
    string getWY();

    /**
     * Gets the name of the file.
     * @return
     *          The name of the file.
     */
    string getInFile();

    /**
     * Gets the content of the file.
     * @return
     *          The contents of the file.
     */
    string getInput();

    /**
     * Removes whitesapce and comments from the contents of the file.
     * @param in
     *          The stream to read from.
     * @return
     *          0 if file read successfully otherwise -1.
     */
    int stripWhitespaceAndComments(istream& in);

private:
    /**
     * Set the file if a valid file is given in the arguments.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     */
    void setFile(int argc, char *argv[]);

    /**
     * Set the help value if -h was given.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     */
    void setHelp(int argc, char *argv[]);

    /**
     * Set the control value if -c was given.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     */
    void setControl(int argc, char*argv[]);

    /**
     * Set the output format if either -f or -v were given.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     */
    void setOutput(int argc, char *argv[]);

    /**
     * Set the number of generations if -g was given.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     * @throws InvalidArgumentException
     *          If value of generation is less than 0.
     */
    void setGenerations(int argc, char *argv[]);

    /**
     * Sets the grid size if -s was given.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     * @throws InvalidArgumentException
     *          If value of grid size is less than 1.
     */
    void setGridSize(int argc, char*argv[]);

    /**
     * Gets a range string if the flag was given.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     * @param flag
     *          The range flag.
     * @return
     *          The string of the range.
     */
    string setRange(int argc, char *argv[], const char *flag);

    /**
     * Gets the position of a flag.
     * @param argc
     *          The number of arguments.
     * @param argv
     *          The array of arguments.
     * @param flag
     *          The flag to get the position of.
     * @return
     *          The position of the given flag.
     */
    int flagPos(int argc, char *argv[], const char *flag);

    /**
     * Removes whitespace from the left of a string.
     * @param str
     *          The string to remove the whitesapce.
     * @return
     *          A string with the whitespace on the left removed.
     */
    string trimLeft(string str);
};

#endif
