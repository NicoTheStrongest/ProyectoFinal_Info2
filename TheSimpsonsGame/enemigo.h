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

#include "fisicas.h"
#include "personaje.h"


class Enemigo : public personaje, public QGraphicsPixmapItem

{
    Q_OBJECT
public:
    explicit Enemigo(QObject *parent = nullptr);
    Enemigo(QPoint posicionInicial, int velocidad, int direccionActual, float columnaInicial, float fila, float ancho, float alto, short int nivel);
    QPoint getPosicion() const;
    void moverArriba();
    void moverAbajo();
    void moverAdelante();
    void moverAtras();

    void cargarEnemigosNivel1(QGraphicsScene *scene);
    void cargarEnemigosNivel2(QGraphicsScene *scene);
    void cargarSpriteNivel(short int nivel);

    void parar();
    bool detenerMovimiento();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void moverNivel1();
    void moverNivel2();
    void moverAntorchas();
    void cambiarSprite();
    void lanzarAntorcha();

signals:

private:
    QPoint posicion;
    QTimer* timer;
    QTimer* timer2;
    QTimer* lanzamiento;
    QPixmap* sprite;
    Fisicas objetoFisico;
    QList<QGraphicsPixmapItem*> antorchas;
    bool control;
    int velocidad, direccionActual, limiteIzquierda, limiteDerecha;
    short int nivel;
    float fila, columna, ancho, alto, columnaInicial;

};

#endif // ENEMIGO_H
