#include <iostream>
#include <fstream>
#include "settings.h"
#include "lifeclass.h"
#include "elementary.h"
#include "brian.h"
#include "world.h"
#include "automatonparser.h"
#include "lifewidget.h"
#include "control.h"
#include <sstream>
#include <QApplication>
#include <QString>

using namespace std;

/**
 * lifegui program that displays grid as a gui
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
        cout << "\nlifegui represents a cellular automaton file as a graphical grid.\n\n";
        cout << "Supported automaton: Life-like, Elementary, and Brian's Brain.\n\n";
        cout << "Supported switches:\n";
        cout << "-h displays the help menu.\n";
        cout << "-g n specifies the desired generation number. n is 0 by default\n";
        cout << "-tx l..h sets the x range for the terrain in the format of low to high (low..high), which overrides the terrain values in input.\n";
        cout << "-ty l..h sets the y range for the terrain in the format of low to high (low..high), which overrides the terrain values in input.\n";
        cout << "-wx l..h sets the x range for the window in the format of low to high (low..high), which overrides the window values in input.\n";
        cout << "-wy l..h sets the y range for the window in the format of low to high (low..high), which overrides the window values in input.\n";
        cout << "-s will set the size in pixels of each square in the grid. If the size is less than 4, grid lines will not be displayed. Grid size is\n";
        cout << "10 by default\n";
        cout << "-c will display a control dialog box to interact with the simulation.\n\n";
        cout << "Button functionality:\n";
        cout << "-Quit    - This will exit the application and close both windows. It should exit without any errors (maybe qt memory issues though).\n";
        cout << "-Restart - This will reset the simulation to generation 0 based on the initial cells of the automaton. If the simulation was started, this will\n";
        cout << "cause it to stop but will not alter the delay value or grid size.\n";
        cout << "-Play    - This will start the simulation based on the delay value. The slider can be adjusted and so can the value in the delay box and the\n";
        cout << "simulation delay will be updated as the simulation continues. Once the simulation has been started, it stopped by pressing Restart, Quit\n";
        cout << "or Step. The simulation simulates one generation at a time.\n";
        cout << "-Step    - This will simulate one generation and then update the GuiWidget. If the simulation was started, this will stop it but will not alter the\n";
        cout << "delay or grid size.\n\n";
        cout << "-Grid size box and slider adjusts the size of the grid squares in pixels\n";
        cout << "-Delay box and slider adjusts the delay between generations in simulation\n";
        return 0;
    }

    if(settings.getInFile().empty()) //if no valid file was given, will read from cin
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

    //create gui grid and show
    QApplication app(argc, argv);
    Control *control = new Control;
    control->init(&app, world, settings.getGenerations(), settings.getGridSize());

    if(settings.controlFlag()) control->show();

    return app.exec();
}
