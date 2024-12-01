#include "personaje.h"

personaje::personaje(QObject *parent)
    : QObject{parent}, vida(100)
{}

void personaje::setEscenario(QGraphicsScene *newEscenario){escenario = newEscenario;}

unsigned int personaje::getAncho() const {return ancho;}
unsigned int personaje::getAltura() const {return altura;}
