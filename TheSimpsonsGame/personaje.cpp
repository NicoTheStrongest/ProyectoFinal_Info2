#include "personaje.h"

personaje::personaje(QObject *parent)
    : QObject{parent}, vida(10), ancho(40), altura(40)
{}

//-------------------SETTERS--------------------------
void personaje::setEscenario(QGraphicsScene *newEscenario){escenario = newEscenario;}

//-------------------GETTERS--------------------------
short personaje::getVida() const{return vida;}
unsigned int personaje::getAncho() const {return ancho;}
unsigned int personaje::getAltura() const {return altura;}
