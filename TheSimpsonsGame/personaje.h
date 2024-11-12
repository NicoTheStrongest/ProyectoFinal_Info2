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
    explicit personaje(QObject *parent = nullptr);
    personaje(Ui::MainWindow *ui);
signals:
private:
    Ui::MainWindow* vista;
    short int getVida() const;
    unsigned int getAncho() const;
    unsigned int getAltura() const;
    void muerte();
    void recibirDanno(short int cantidad);


signals:

private:
    short int vida;
    unsigned int ancho, altura, keys[8], danno;
};

#endif // PERSONAJE_H
