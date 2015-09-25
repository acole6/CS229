#include <QtGui>
#include "control.h"
#include <sstream>
#include <vector>
#include <iostream>

/**
 * Implementation of control.h
 * @author Alex Cole
 */

 /**
  * Default constructor that sets up the control dialog.
  * @param parent
  *             The parent widget. Default is NULL.
  */
Control::Control(QWidget *parent)
    :QDialog(parent)
{
    delay = 4000;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(playSimulation()));

    QHBoxLayout *gridSizeLayout = new QHBoxLayout;
    gridSizeLabel = new QLabel("Grid size: ");
    gridSizeSpinBox = new QSpinBox;
    gridSizeSpinBox->setRange(1, 100);
    gridSizeSlider = new QSlider(Qt::Horizontal);
    gridSizeSlider->setRange(1, 100);
    connect(gridSizeSpinBox, SIGNAL(valueChanged(int)), gridSizeSlider, SLOT(setValue(int)));
    connect(gridSizeSlider, SIGNAL(valueChanged(int)), gridSizeSpinBox, SLOT(setValue(int)));
    connect(gridSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setGridSize()));
    gridSizeLayout->addWidget(gridSizeLabel);
    gridSizeLayout->addWidget(gridSizeSpinBox);
    gridSizeLayout->addWidget(gridSizeSlider);

    QHBoxLayout *delayLayout = new QHBoxLayout;
    delayLabel = new QLabel("Delay: ");
    delaySpinBox = new QSpinBox;
    delaySpinBox->setRange(0, 10000);
    delaySlider = new QSlider(Qt::Horizontal);
    delaySlider->setRange(0, 10000);
    connect(delaySpinBox, SIGNAL(valueChanged(int)), delaySlider, SLOT(setValue(int)));
    connect(delaySlider, SIGNAL(valueChanged(int)), delaySpinBox, SLOT(setValue(int)));
    connect(delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(setDelay()));
    delaySpinBox->setValue(delay);
    delayLayout->addWidget(delayLabel);
    delayLayout->addWidget(delaySpinBox);
    delayLayout->addWidget(delaySlider);

    QHBoxLayout *genLayout = new QHBoxLayout;
    genLabel = new QLabel("Generation: ");
    genNumLabel = new QLabel("0");
    genLayout->addWidget(genLabel);
    genLayout->addWidget(genNumLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    quit = new QPushButton("Quit");
    restart = new QPushButton("Restart");
    play = new QPushButton("Play");
    step = new QPushButton("Step");
    buttonLayout->addWidget(quit);
    buttonLayout->addWidget(restart);
    buttonLayout->addWidget(play);
    buttonLayout->addWidget(step);

    connect(step, SIGNAL(clicked()), this, SLOT(stepClicked()));
    connect(restart, SIGNAL(clicked()), this, SLOT(restartClicked()));
    connect(play, SIGNAL(clicked()), this, SLOT(playClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridSizeLayout);
    mainLayout->addLayout(delayLayout);
    mainLayout->addLayout(genLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

/**
 * Destructor
 */
Control::~Control() {}

/**
 * Initializes control dialog that could not be initialized in the constructor.
 * @param app
 *              The application for the dialog box.
 * @param world
 *              The cellular automaton world.
 * @param generations
 *              The initial generation.
 * @param gridSize
 *              The size of the grid blocks in pixels.
 */
void Control::init(QApplication *app, World *world, int generations, int gridSize)
{
    this->world = world;
    this->gridSize = gridSize;

    widget = new GuiWidget;
    vector<vector<Color>> colorWorld = this->world->toColor();
    string automatonName = this->world->getAutomaton()->getName();
    widget->init(colorWorld, gridSize, automatonName);
    widget->show();

    string name = automatonName + " Controls";
    setWindowTitle(name.c_str());

    gridSizeSpinBox->setValue(gridSize);

    setGenNumLabel(generations);

    connect(quit, SIGNAL(clicked()), app, SLOT(quit()));
}

/**
 * Simulates the world by one generation. This will
 * stop the simulation if it is currently in progress.
 */
void Control::stepClicked()
{
    timer->stop();
    simulateOneGen();
}

/**
 * Sets the simulation back to the initial state of the world. This
 * will stop the simulation if it is currently in progress.
 */
void Control::restartClicked()
{
    timer->stop();
    setGenNumLabel(0);
    world->reset();
    updateWidget();
}

/**
 * Starts the simulation and simulates one generation at a time based on
 * the delay.
 */
void Control::playClicked()
{
    timer->start(delay);
}

/**
 * Changes the grid size if it has been adjusted by the spin box or slider.
 */
void Control::setGridSize()
{
    gridSize = gridSizeSpinBox->value();
    updateWidget();
}

/**
 * Changes the delay if it has been adjusted by the spin box or slider.
 * Does not stop the simulation.
 */
void Control::setDelay()
{
    delay = delaySpinBox->value();
    if(timer != NULL && timer->isActive()) timer->setInterval(delay);
}

/**
 * Starts the simulation
 */
void Control::playSimulation()
{
    simulateOneGen();
}

/**
 * Updates the widget based on changes made in the control dialog box.
 */
void Control::updateWidget()
{
    vector<vector<Color>> colorWorld = world->toColor();
    widget->updateImage(gridSize, colorWorld);
}

/**
 * Sets the generation value in genNumLabel
 * @param gen
 *          The generation that genNumLabel is to be set to.
 */
void Control::setGenNumLabel(int gen)
{
    stringstream num;
    num << gen;
    genNumLabel->setText(num.str().c_str());
}

/**
 * Converts the number in genNumLabel to an int.
 * @return
 *          genNumLabel value as an int.
 */
int Control::genNumLabelToInt()
{
    string text = genNumLabel->text().toStdString();
    return atoi(text.c_str());
}

/**
 * Simulates the world by one generation.
 */
void Control::simulateOneGen()
{
    int gen = genNumLabelToInt();
    gen++;
    setGenNumLabel(gen);

    world->simulate(1);
    updateWidget();
}
