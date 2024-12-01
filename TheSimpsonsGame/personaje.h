#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <Qpoint>
#include <QKeyEvent>

class personaje : public QObject
{
    Q_OBJECT

public:
    explicit personaje(QObject *parent = nullptr);

    //SETTERS
    void setEscenario(QGraphicsScene* newEscenario);

    //GETTERS
    short int getVida() const;
    unsigned int getAncho() const;
    unsigned int getAltura() const;
private:
    //ATRIBUTOS
    QGraphicsScene* escenario;
    short int vida;
    unsigned int ancho, altura;
};

#endif // PERSONAJE_H
