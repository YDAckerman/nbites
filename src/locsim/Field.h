#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPointer>
#include <QGridLayout>
#include <vector>
#include "FieldPlayer.h"

class Field : public QWidget
{
    Q_OBJECT

 public:
    Field(int fWidth, int fHeight, QWidget *parent = 0);
    ~Field();

    void drawFieldLines();

    void resetField();

    FieldPlayer *getPlayer();

    QPointer<QGraphicsScene> getField() { return field; }

public slots:
    void next();

private:
    QPointer<QGraphicsScene> field;
    QPointer<QGraphicsView> view;

    int fieldWidth;
    int fieldHeight;

    int framesElapsed;

    FieldPlayer *fieldPlayer;

    QPointer<QTimer> timer;
};

#endif // FIELD_H
