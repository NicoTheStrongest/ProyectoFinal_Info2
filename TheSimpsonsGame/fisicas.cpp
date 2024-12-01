#include "fisicas.h"

Fisicas::Fisicas(QObject *parent)
    : QObject{parent}
{
    tiempo = 0;
    velocidadY = 0;
    gravedad= 9.81;
}

//-------------------SETTERS--------------------------
void Fisicas::setTiempo(double newTiempo){this->tiempo = newTiempo;}

//-------------------METODOS--------------------------
void Fisicas::aplicarGravedad(QPoint &posicion, int velocidadDefecto){
    tiempo += 0.050;
    //int equis = posicion.x();
    //if(ultimaDireccionx == "derecha"){equis += velocidadDefecto;}
    //else if(ultimaDireccionx == "izquierda"){equis -= velocidadDefecto;}
    int ye = posicion.y();
    velocidadY = velocidadDefecto + gravedad*tiempo;
    velocidadY = (velocidadY > 15) ? 15 : velocidadY;
    //double nuevaY = ye + (velocidadY * tiempo - 0.5 * gravedad * tiempo * tiempo);
    double nuevaY = ye + velocidadY;
    //posicion.setX(equis);
    posicion.setY(nuevaY);
}

void Fisicas::inicializarMovimientoCircular(qreal xCentro, qreal yCentro, qreal radio,
                                        qreal velocidadAngular, qreal velocidadRotacion,
                                        int X, int Y){
    this->centro = QPoint(xCentro, yCentro);
    this->radio = radio;
    this->anguloActual = 0;
    this->velocidadAngular=velocidadAngular;
    this->velocidadRotacion=velocidadRotacion;
    this->desplazamientoX=X;
    this->desplazamientoY=Y;
}

void Fisicas::aplicarMovimientocircular(QPointF& posicion, qreal& rotacionSierra) {
    this->anguloActual += this->velocidadAngular;
    if (this->anguloActual >= 360) this->anguloActual -= 360;

    qreal radianes = qDegreesToRadians(this->anguloActual);
    qreal x = this->desplazamientoX + this->centro.x() + this->radio * qCos(radianes);
    qreal y = this->desplazamientoY + this->centro.y() + this->radio * qSin(radianes);
    posicion.setX(x);
    posicion.setY(y);

    rotacionSierra += this->velocidadRotacion;
    if (rotacionSierra >= 360) rotacionSierra -= 360;
}

