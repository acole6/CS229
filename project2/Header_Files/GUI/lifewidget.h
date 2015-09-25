#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <vector>
#include "world.h"

using namespace std;

/**
 * class to paint a grid representation of a world
 * @author Alex Cole
 */
class GuiWidget : public QWidget
{
protected:
    /**
     * rows in the grid
     */
    int rows;

    /**
     * columns in the grid
     */
    int columns;

    /**
     * size of the blocks to be painted in pixels
     */
    int gridSize;

    /**
     * label to contain the image
     */
    QLabel *imageLabel;

    /**
     * image that the grid will be painted on
     */
    QImage *image;

    /**
     * allows for scroll bars
     */
    QScrollArea *scroll;

    /**
     * layout of the gui
     */
    QHBoxLayout *lay;

public:
    /**
     * Default constructor that takes in an optional parent widget.
     * @param parent
     *              The parent QWidget to this object. Default is NULL.
     */
    GuiWidget(QWidget *parent = 0);

    /**
     * Destructor
     */
    ~GuiWidget();

    /**
     * Initializes the widget based the given name, grid size and color world.
     * @param world
     *              The color world used to paint the grid.
     * @param gridSize
     *              The size of the blocks in the grid.
     * @param name
     *              The name of the cellular automaton.
     */
    void init(vector<vector<Color>> world, int gridSize, string name);

    /**
     * Paints the grid onto the widget.
     * @param image
     *              The image to paint the grid on.
     * @param world
     *              The color world to be painted.
     */
    void paint(QImage *image, vector<vector<Color>> &world);

    /**
     * Updates the grid and the layout.
     * @param gS
     *              The size of the grid blocks in pixels.
     * @param world
     *              The color world to update the image.
     */
    void updateImage(int gS, vector<vector<Color>> &world);

    /**
     * Removes the previous layout.
     * @param layout
     *              The layout to be removed.
     */
    void removeLayout(QLayout *layout);
};

#endif
