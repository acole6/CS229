#include "lifewidget.h"
#include <QPainter>
#include <QColor>
#include <QPixmap>
#include <iostream>

/**
 * Implementation of lifewidget.h
 * @author Alex Cole
 */

/**
 * Default constructor that takes in an optional parent widget.
 * @param parent
 *              The parent QWidget to this object. Default is NULL.
 */
GuiWidget::GuiWidget(QWidget *parent)
    : QWidget(parent)
{
    imageLabel = NULL;
    image = NULL;
    scroll = NULL;
    lay = new QHBoxLayout;
    this->setLayout(lay);
}

/**
 * Destructor
 */
GuiWidget::~GuiWidget() {}

/**
 * Initializes the widget based the given name, grid size and color world.
 * @param world
 *              The color world used to paint the grid.
 * @param gridSize
 *              The size of the blocks in the grid.
 * @param name
 *              The name of the cellular automaton.
 */
void GuiWidget::init(vector<vector<Color>> world, int gridSize, string name)
{
    rows = world.size();
    columns = world[0].size();
    this->gridSize = gridSize;
    this->setWindowTitle(name.c_str());
    updateImage(this->gridSize, world);
}


/**
 * Updates the grid and the layout.
 * @param gS
 *              The size of the grid blocks in pixels.
 * @param world
 *              The color world to update the image.
 */
void GuiWidget::updateImage(int gS, vector<vector<Color>> &world)
{
    removeLayout(this->layout());
    delete lay;

    gridSize = gS;
    int colGrid = gridSize < 4 ? 0 : columns - 1; //determines grid lines
    int rowGrid = gridSize < 4 ? 0 : rows - 1;
    int width = (columns * gridSize) + colGrid;
    int height = (rows * gridSize) + rowGrid;

    imageLabel = new QLabel;
    image = new QImage(width, height, QImage::Format_RGB32);
    image->fill(QColor(245, 245, 220)); //makes grid lines beige
    paint(image, world);
    imageLabel->setPixmap(QPixmap::fromImage(*image));

    scroll = new QScrollArea();
    scroll->setBackgroundRole(QPalette::Dark);
    scroll->setWidget(imageLabel);

    lay = new QHBoxLayout();
    lay->addWidget(scroll);
    setLayout(lay);
}

/**
 * Paints the grid onto the widget.
 * @param image
 *              The image to paint the grid on.
 * @param world
 *              The color world to be painted.
 */
void GuiWidget::paint(QImage *image, vector<vector<Color>> &world)
{
    QPainter painter(image);

    int rowY = 0;
    int colX = 0;
    for(int row = 0; row < rows; row++)
    {
        if(gridSize < 4) //if grid size is less than 4, then no line between rows
        {
            rowY = row * gridSize;
        }
        else
        {
            rowY = (row * gridSize) + row;
        }
        for(int col = 0; col < columns; col++)
        {
            if(gridSize < 4) //if grid size is less than 4, then no line between columns
            {
                colX = col * gridSize;
            }
            else
            {
                colX = (col * gridSize) + col;
            }

            QColor color(world[row][col].getRed(), world[row][col].getGreen(), world[row][col].getBlue());
            painter.fillRect(colX, rowY, gridSize, gridSize, color);;
        }
    }
}

/**
 * Removes the previous layout.
 * @param layout
 *              The layout to be removed.
 */
void GuiWidget::removeLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            removeLayout(item->layout());
            delete item->layout();
        }

        if (item->widget()) delete item->widget();

        delete item;
    }
}

