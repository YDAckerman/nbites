#include "Field.h"

Field::Field(int fWidth, int fHeight, QWidget *parent)
    : QWidget(parent), fieldWidth(fWidth), fieldHeight(fHeight), framesElapsed(0)
{
    // Setup the field.
    field.setBackgroundBrush(Qt::green);
    field.setSceneRect(0, 0, fieldWidth, fieldHeight);

    // Draw field lines & landmarks.
    drawFieldLines();

    // Draw players.
    drawFieldPlayers();

    // Setup the view.
    view.setParent(parent);
    view.setScene(&field);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.resize(fieldWidth, fieldHeight);
    view.show();
}

Field::~Field()
{
}

void Field::addPlayer(FieldPlayer *player)
{
    players.push_back(player);
}

void Field::nextFrame()
{
    framesElapsed++;

    for(int i = 0; i < players.size(); ++i)
        players[i]->nextFrame();
}

void Field::drawFieldLines()
{
    // Left & right sidelines.
    field.addRect(0, 0, 5, 400, QPen(Qt::white), QBrush(Qt::white));
    field.addRect(595, 0, 5, 400, QPen(Qt::white), QBrush(Qt::white));

    // Top & bottom sidelines.
    field.addRect(0, 0, 600, 5, QPen(Qt::white), QBrush(Qt::white));
    field.addRect(0, 395, 600, 5, QPen(Qt::white), QBrush(Qt::white));

    // Midline.
    field.addRect(295, 0, 5, 400, QPen(Qt::white), QBrush(Qt::white));
    field.addEllipse(238, 140, 120, 120, QPen(QBrush(Qt::white), 5));

    // Blue goal box & posts.
    field.addRect(0, 80, 60, 5, QPen(Qt::white), QBrush(Qt::white));
    field.addRect(0, 300, 60, 5, QPen(Qt::white), QBrush(Qt::white));
    field.addRect(60, 80, 6, 225, QPen(Qt::white), QBrush(Qt::white));
    field.addEllipse(QRect(2, 78, 10, 10), QPen(Qt::blue), QBrush(Qt::blue));
    field.addEllipse(QRect(2, 298, 10, 10), QPen(Qt::blue), QBrush(Qt::blue));

    // Yellow goal box & posts.
    // @todo.
}

void Field::drawFieldPlayers()
{
    for(int i = 0; i < players.size(); ++i)
    {
        players[i]->draw(&field);
    }
}

void Field::resetField()
{

}
