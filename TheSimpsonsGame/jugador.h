#ifndef JUGADOR_H
#define JUGADOR_H

#include <QApplication>
#include <QObject>
#include <Qpoint>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

#include "personaje.h"


class Jugador : public personaje, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Jugador(QObject *parent = nullptr);
    Jugador(QGraphicsScene* escena);
    QPoint getPosicion() const;
    void cargarPersonaje(QGraphicsScene *scene);
    void keyPressEvent(QKeyEvent *event);
    void moverAdelante();
    void moverAtras();
    void moverArriba();
    void moverAbajo();
    void atacar();

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    float filas, columnas, ancho, alto;
signals:
public slots:
    void cambiarSprite();
private:
    QTimer* sprite;
    QPixmap* pixmap;
    QPoint posicion;
    short int velocidad, direccionActual;

};

#endif // JUGADOR_H
