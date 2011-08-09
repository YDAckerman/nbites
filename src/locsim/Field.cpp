#include "Field.h"

#include <iostream>

Field::Field(int fWidth, int fHeight, QWidget *parent)
    : QWidget(parent), fieldWidth(fWidth), fieldHeight(fHeight), framesElapsed(0)
{
    // Setup the field.
    field = new QGraphicsScene();
    field->setBackgroundBrush(Qt::green);
    field->setSceneRect(0, 0, fieldWidth, fieldHeight);

    // Draw field lines & landmarks.
    drawFieldLines();

    // Setup the view.
    view = new QGraphicsView(field, parent);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->resize(fieldWidth, fieldHeight);
    view->show();

    fieldPlayer = new FieldPlayer(100, 100, 30, "Annika", 1, 2, field);

    timer = new QTimer(this);

    connect(timer,
            SIGNAL(timeout()),
            this,
            SLOT(next()));

    timer->start(1000);
}

Field::~Field()
{
}

void Field::next()
{
    framesElapsed++;

    std::cout << "Next frame (" << framesElapsed << ")." << std::endl;

    fieldPlayer->nextFrame();

    field->update();
}

void Field::drawFieldLines()
{
    // Left & right sidelines.
    field->addRect(0, 0, 5, 400, QPen(Qt::white), QBrush(Qt::white));
    field->addRect(595, 0, 5, 400, QPen(Qt::white), QBrush(Qt::white));

    // Top & bottom sidelines.
    field->addRect(0, 0, 600, 5, QPen(Qt::white), QBrush(Qt::white));
    field->addRect(0, 395, 600, 5, QPen(Qt::white), QBrush(Qt::white));

    // Midline.
    field->addRect(295, 0, 5, 400, QPen(Qt::white), QBrush(Qt::white));
    field->addEllipse(238, 140, 120, 120, QPen(QBrush(Qt::white), 5));

    // Blue goal box & posts.
    field->addRect(0, 80, 60, 5, QPen(Qt::white), QBrush(Qt::white));
    field->addRect(0, 300, 60, 5, QPen(Qt::white), QBrush(Qt::white));
    field->addRect(60, 80, 5, 225, QPen(Qt::white), QBrush(Qt::white));
    field->addEllipse(QRect(2, 120, 10, 10), QPen(Qt::blue), QBrush(Qt::blue));
    field->addEllipse(QRect(2, 260, 10, 10), QPen(Qt::blue), QBrush(Qt::blue));

    // Yellow goal box & posts.
    field->addRect(535, 80, 60, 5, QPen(Qt::white), QBrush(Qt::white));
    field->addRect(535, 300, 60, 5, QPen(Qt::white), QBrush(Qt::white));
    field->addRect(535, 80, 5, 225, QPen(Qt::white), QBrush(Qt::white));
    field->addEllipse(QRect(588, 120, 10, 10), QPen(Qt::yellow), QBrush(Qt::yellow));
    field->addEllipse(QRect(588, 260, 10, 10), QPen(Qt::yellow), QBrush(Qt::yellow));
}

void Field::resetField()
{

}

FieldPlayer *Field::getPlayer()
{
    return fieldPlayer;
}
