#include "personaje.h"

personaje::personaje(QObject *parent)
    : QObject{parent}, vida(5), ancho(20), altura(20)
{}

void personaje::setEscenario(QGraphicsScene *newEscenario){escenario = newEscenario;}

unsigned int personaje::getAncho() const {return ancho;}
unsigned int personaje::getAltura() const {return altura;}
