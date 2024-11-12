#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : personaje{parent}, direccionActual(2), velocidad(2), posicion(0, 370)
{
    setRect(0, 0, 20, 20);
    setBrush(QBrush(Qt::yellow));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

QPoint Jugador::getPosicion() const {return posicion;}

void Jugador::cargarPersonaje(QGraphicsScene *scene){
    scene->addItem(this);
    setPos(posicion);
}

void Jugador::moverAdelante(){
    posicion.setX(posicion.x() + velocidad);
    setPos(posicion);
    direccionActual = 0;
    qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x();
}

void Jugador::moverAtras(){
    posicion.setX(posicion.x() - velocidad);
    setPos(posicion);
    direccionActual = 1;
     qDebug() << "Moviendo atrás, nueva posicion X:" << posicion.x();
}
void Jugador::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Left:
    {
        moverAtras();
        break;
    }
    case  Qt::Key_A:
    {
        moverAtras();
        break;
    }
    case Qt::Key_Right:
    {
        moverAdelante();
        break;
    }
    case Qt::Key_D:
    {
        moverAdelante();
        break;
    }
    default:
        break;
    }
}


void Jugador::moverEndireccionActual(){
    switch(direccionActual){
    case 0:
        moverAdelante();
        break;
    case 1:
        moverAtras();
        break;
    default:
        break;
    }
}


