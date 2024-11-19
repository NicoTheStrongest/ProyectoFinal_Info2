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
    short int getPuntos() const;
    short int getVida() const;
    bool getControl() const;
    bool finalizarNivel();
    void cargarPersonaje(QGraphicsScene *scene);
    void keyPressEvent(QKeyEvent *event);
    void moverAdelante();
    void moverAtras();
    void moverArriba();
    void moverAbajo();
    void saltar();
    void aumentarPuntos();
    void disminuirVida();
    void parar();
    void atacar();

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    float filas, columnas, ancho, alto;
signals:
    void puntajeCambiado(short int nuevoPuntaje);
    void vidaCambio(short int nuevaVida);
public slots:
    void cambiarSprite();
private:
    QTimer* sprite;
    QPixmap* pixmap;
    QPoint posicion;
    bool control;
    short int velocidad, direccionActual, puntos, vida;

};

#endif // JUGADOR_H
