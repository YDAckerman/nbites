#include "simulatorwindow.h"

SimulatorWindow::SimulatorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setup the main window.
    setFixedSize(800, 800);

    // Create the field.
    soccerField = new Field(FIELD_WIDTH, FIELD_HEIGHT, this);

    // Add a test player.
    //FieldPlayer *newPlayer = new FieldPlayer(100, 100, 30, "Annika", 1, 2, soccerField->getField());
    //soccerField->setPlayer(newPlayer);

    Odometry newOdo(2, 0, 20);
    soccerField->getPlayer()->setWalkOdometry(newOdo);
}

SimulatorWindow::~SimulatorWindow()
{
}
