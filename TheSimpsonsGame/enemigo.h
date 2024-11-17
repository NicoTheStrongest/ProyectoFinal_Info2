#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QApplication>
#include <Qpoint>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>
#include "personaje.h"


class Enemigo : public personaje, public QGraphicsRectItem

{
    Q_OBJECT
public:
    explicit Enemigo(QObject *parent = nullptr);
    Enemigo(QPoint posicionInicial, int velocidad, int direccionActual);
    QPoint getPosicion() const;
    void moverArriba();
    void moverAbajo();
    void cargarEnemigosNivel1(QGraphicsScene *scene);
    void cargarEnemigosNivel2(QGraphicsScene *scene);
    void cargarEnemigosNivel3(QGraphicsScene *scene);
    void parar();
    bool detenerMovimiento();

public slots:
    void mover();

signals:

private:
    QPoint posicion;
    QTimer* timer;
    bool control;
    int velocidad, direccionActual;

};

#endif // ENEMIGO_H
