#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QtGui/QMainWindow>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include "Field.h"
#include "FieldPlayer.h"

enum
{
    FIELD_WIDTH = 600,
    FIELD_HEIGHT = 400
};

class SimulatorWindow : public QMainWindow
{
    Q_OBJECT

public:
    SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();

private:
    QPointer<Field> soccerField;
    QGroupBox *simulationControls;
};

#endif // SIMULATORWINDOW_H
