#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <Qpoint>
#include <QKeyEvent>

#include "sprites.h"
#include "fisicas.h"

class personaje : public QObject
{
    Q_OBJECT

public:
    sprites personalSprite;

    explicit personaje(QObject *parent = nullptr);

    void setEscenario(QGraphicsScene* newEscenario);

    short int getVida() const;
    unsigned int getAncho() const;
    unsigned int getAltura() const;
signals:

private:
    void muerte();
    void recibirDanno(short int cantidad);

    QGraphicsScene* escenario;
    short int vida;
    unsigned int ancho, altura, keys[8], danno;
};

#endif // PERSONAJE_H
