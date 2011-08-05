#include "simulatorwindow.h"

SimulatorWindow::SimulatorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setup the main window.
    setFixedSize(800, 800);

    // Create the field.
    soccerField = new Field(FIELD_WIDTH, FIELD_HEIGHT, this);

    Odometry newOdo(2, 0, 20);
    soccerField->getPlayer()->setWalkOdometry(newOdo);
}

SimulatorWindow::~SimulatorWindow()
{
}
