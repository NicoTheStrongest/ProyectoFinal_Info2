#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <Qpoint>
#include <QGraphicsRectItem>
#include "personaje.h"


class Jugador : public personaje, public virtual QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Jugador(QObject *parent = nullptr);
    QPoint getPosicion() const;
    void cargarPersonaje(QGraphicsScene *scene);
    void keyPressEvent(QKeyEvent *event);
    void moverAdelante();
    void moverAtras();
    void moverEndireccionActual();
    void atacar();

signals:

private:
    QPoint posicion;
    short int velocidad, direccionActual;

};

#endif // JUGADOR_H
