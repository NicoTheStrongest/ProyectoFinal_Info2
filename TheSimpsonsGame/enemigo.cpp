#include "enemigo.h"

Enemigo::Enemigo(QObject *parent)
    : personaje{parent}
{}

Enemigo::Enemigo(QPoint posicionInicial, int velocidad, int direccionActual)
    :posicion(posicionInicial), velocidad(velocidad), direccionActual(direccionActual), control(true)
{
    setRect(0, 0, 26, 30);
    setBrush(QBrush(Qt::black));
    setPos(posicion);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mover()));
    timer->start(300);
}

void Enemigo::moverArriba(){
    if(posicion.y() - velocidad > 340){
        posicion.setY(posicion.y() - velocidad);
        setPos(posicion);
        direccionActual = 0;
        qDebug() << "Moviendo arriba, nueva posicion X:" << posicion.x();
    }
}

void Enemigo::moverAbajo(){
    if(posicion.y() + velocidad < 480){
        posicion.setY(posicion.y() + velocidad);
        setPos(posicion);
        direccionActual = 1;
        qDebug() << "Moviendo abajo, nueva posicion X:" << posicion.x();
    }
}
bool Enemigo::detenerMovimiento(){
    return control;
}

void Enemigo::parar(){
    control = false;
}
void Enemigo::mover(){
    if(!detenerMovimiento()){return;}
    if(posicion.y() >= 468){
        direccionActual = 0;
    }
    else if(posicion.y() <= 369){
        direccionActual = 1;
    }
    if(direccionActual == 1){
        moverAbajo();
    }
    else if(direccionActual == 0){
        moverArriba();
    }
}

void Enemigo::cargarEnemigosNivel1(QGraphicsScene *scene){
    Enemigo* enemigo1 = new Enemigo(QPoint(358, 369), 2, 1);
    scene->addItem(enemigo1);
    enemigo1->setData(0, "enemigo");
    Enemigo* enemigo2 = new Enemigo(QPoint(768, 468), 2, 0);
    scene->addItem(enemigo2);
    enemigo2->setData(0, "enemigo");
    Enemigo* enemigo3 = new Enemigo(QPoint(1158, 369), 2, 1);
    scene->addItem(enemigo3);
    enemigo3->setData(0, "enemigo");
    Enemigo* enemigo4 = new Enemigo(QPoint(1570, 468), 2, 0);
    scene->addItem(enemigo4);
    enemigo4->setData(0, "enemigo");
}
