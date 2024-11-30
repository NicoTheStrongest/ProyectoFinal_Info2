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


class Enemigo : public personaje, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    explicit Enemigo(QObject *parent = nullptr);
    Enemigo(QPoint posicionInicial, int velocidad, int direccionActual, float columnaInicial, float fila, float ancho);
    QPoint getPosicion() const;
    void moverArriba();
    void moverAbajo();
    void moverAdelante();
    void moverAtras();

    void cargarEnemigosNivel1(QGraphicsScene *scene);
    void cargarEnemigosNivel2(QGraphicsScene *scene);
    void cargarEnemigosNivel3(QGraphicsScene *scene);
    void parar();
    bool detenerMovimiento();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void mover();
    void cambiarSprite();

signals:

private:
    QPoint posicion;
    QTimer* timer;
    QPixmap* sprite;
    QVector<Enemigo*> enemigosNivel1;
    bool control;
    int velocidad, direccionActual;
    float fila, columna, ancho, alto, columnaInicial;

};

#endif // ENEMIGO_H
