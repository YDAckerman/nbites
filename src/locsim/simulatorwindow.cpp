#include "simulatorwindow.h"

SimulatorWindow::SimulatorWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Setup the main window.
    setFixedSize(800, 800);

    // Create the field.
    soccerField = new Field(FIELD_WIDTH, FIELD_HEIGHT, this);

    // Add a test player.
    FieldPlayer testPlayer(100, 100, 30, "Annika", 1, 2);
    soccerField->addPlayer(&testPlayer);
    soccerField->drawFieldPlayers();
}

SimulatorWindow::~SimulatorWindow()
{
    delete soccerField;
    soccerField = 0;
}
