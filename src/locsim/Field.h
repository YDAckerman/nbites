#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include "FieldPlayer.h"

class Field : public QWidget
{
 public:
    Field(int fWidth, int fHeight, QWidget *parent = 0);
    ~Field();

    void addPlayer(FieldPlayer *player);
    void nextFrame();

    void drawFieldLines();

    void drawFieldPlayers();

    void resetField();

private:
    QGraphicsScene field;
    QGraphicsView view;

    int fieldWidth;
    int fieldHeight;

    int framesElapsed;

    std::vector<FieldPlayer *> players;
};

#endif // FIELD_H
