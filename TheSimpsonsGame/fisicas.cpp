#include "fisicas.h"

Fisicas::Fisicas(QObject *parent)
    : QObject{parent}
{
    velocidad = 0;
}

void Fisicas::aplicarGravedad(QPoint &posicion, int velocidadDefecto){
    int equis = posicion.x();
    int ye = posicion.y();

    velocidad = velocidadDefecto + 0.4;
    ye = ye + velocidad;
    posicion.setX(equis);
    posicion.setY(ye);
}
