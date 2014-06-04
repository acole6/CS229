#ifndef CONTROL_H
#define CONTROL_H

#include "lifewidget.h"
#include "world.h"
#include <QApplication>
#include <QDialog>

class QLabel;
class QSpinBox;
class QSlider;
class QPushButton;
class QTimer;

/**
 * control dialog box
 * @author Alex Cole
 */
class Control : public QDialog
{
	Q_OBJECT
	
public:
	/**
	 * Default constructor that sets up the control dialog.
	 * @param parent
	 *				The parent widget. Default is NULL.
	 */
	Control(QWidget *parent = 0);
	
	/**
	 * Destructor
	 */
	~Control();
	
	/**
	 * Initializes control dialog that could not be initialized in the constructor.
	 * @param app
	 *				The application for the dialog box.
	 * @param world
	 *				The cellular automaton world.
	 * @param generations
	 *				The initial generation.
	 * @param gridSize
	 *				The size of the grid blocks in pixels.
	 */
	void init(QApplication *app, World *world, int generations, int gridSize);
	
	/**
	 * Updates the widget based on changes made in the control dialog box.
	 */
	void updateWidget();
	
	/**
	 * Sets the generation value in genNumLabel
	 * @param gen
	 *			The generation that genNumLabel is to be set to.
	 */
	void setGenNumLabel(int gen);
	
	/**
	 * Converts the number in genNumLabel to an int.
	 * @return
	 *			genNumLabel value as an int.
	 */
	int genNumLabelToInt();
	
	/**
	 * Simulates the world by one generation.
	 */
	void simulateOneGen();
	 
private slots:
	/**
	 * Simulates the world by one generation. Does not
	 * stop the simulation if the play button has been pressed.
	 */
	void stepClicked();
	
	/**
	 * Sets the simulation back to the initial state of the world. Does
	 * not stop the simulation if the play button has been pressed.
	 */
	void restartClicked();
	
	/**
	 * Starts the simulation and simulates one generation at a time based on
	 * the delay.
	 */
	void playClicked();
	
	/**
	 * Changes the grid size if it has been adjusted by the spin box or slider.
	 */
	void setGridSize();
	
	/**
	 * Changes the delay if it has been adjusted by the spin box or slider.
	 */
	void setDelay();
	
	/**
	 * Starts the simulation
	 */
	void playSimulation();
	
private:
	/**
	 * grid size label
	 */
	QLabel *gridSizeLabel;
	
	/**
	 * delay label
	 */
	QLabel *delayLabel;
	
	/**
	 * generation label
	 */
	QLabel *genLabel;
	
	/**
	 * current generation number label
	 */
	QLabel *genNumLabel;
	
	/**
	 * grid size spin box
	 */
	QSpinBox *gridSizeSpinBox;
	
	/**
	 * delay spin box
	 */
	QSpinBox *delaySpinBox;
	
	/**
	 * grid size slider
	 */
	QSlider *gridSizeSlider;
	
	/**
	 * delay slider
	 */
	QSlider *delaySlider;
	
	/**
	 * quit button
	 */
	QPushButton *quit;
	
	/**
	 * restart button
	 */
	QPushButton *restart;
	
	/**
	 * play button
	 */
	QPushButton *play;
	
	/**
	 * step button
	 */
	QPushButton *step;
	
	/**
	 * timer for simulation based on delay
	 */
	QTimer *timer;
	
	/**
	 * world of the automaton
	 */
	World *world;
	
	/**
	 * gui of the grid
	 */
	GuiWidget *widget;
	
	/**
	 * the grid size
	 */
	int gridSize;
	
	/**
	 * delay for the timer
	 */
	int delay;
};

#endif
