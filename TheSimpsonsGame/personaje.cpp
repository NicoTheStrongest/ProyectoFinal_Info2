#include "personaje.h"

personaje::personaje(QObject *parent)
    : QObject{parent}
{}

//-------------------SETTERS--------------------------
void personaje::setEscenario(QGraphicsScene *newEscenario){escenario = newEscenario;}

//-------------------GETTERS--------------------------
unsigned int personaje::getAncho() const {return ancho;}
unsigned int personaje::getAltura() const {return altura;}
