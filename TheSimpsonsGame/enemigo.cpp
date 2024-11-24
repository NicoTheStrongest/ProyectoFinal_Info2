#include "enemigo.h"

Enemigo::Enemigo(QObject *parent)
    : personaje{parent}
{}

Enemigo::Enemigo(QPoint posicionInicial, int velocidad, int direccionActual, float columnaInicial, float fila, float ancho)
    :posicion(posicionInicial), velocidad(velocidad), direccionActual(direccionActual), control(true), columnaInicial(columnaInicial), fila(fila), ancho(ancho), alto(85)
{
    setPos(posicion);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(cambiarSprite()));
    timer->start(500);

    sprite = new QPixmap(":/sprites/NPC1.png");
    QColor colorAzul(151,198,222,255);
    sprite->setMask(sprite->createMaskFromColor(colorAzul.rgb(), Qt::MaskInColor));
    connect(timer, SIGNAL(timeout()), this, SLOT(mover()));
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

void Enemigo::moverAdelante(){
    if(posicion.x() + velocidad < 1854){
        posicion.setX(posicion.x() + velocidad);
        setPos(posicion);
        direccionActual = 0;
        qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
    }
}

void Enemigo::moverAtras(){
    if(posicion.x() - velocidad > 0){
        posicion.setX(posicion.x() - velocidad);
        setPos(posicion);
        direccionActual = 1;
        qDebug() << "Moviendo atrás, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
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

QRectF Enemigo::boundingRect() const
{
    return QRectF(-ancho / 2, -alto / 2, ancho, alto);
}

QPainterPath Enemigo::shape() const {
    QPainterPath rectangulo;
    rectangulo.addRect(boundingRect());
    return rectangulo;
}

void Enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float filaInicial = fila * alto;
    painter->drawPixmap(-ancho / 2, -alto / 2, *sprite , columna, filaInicial, ancho, alto);
}


void Enemigo::cargarEnemigosNivel1(QGraphicsScene *scene){
    Enemigo* enemigo1 = new Enemigo(QPoint(380, 369), 2, 1, 0, 0.3, 44);
    enemigo1->setData(0, "enemigo");
    scene->addItem(enemigo1);
    qDebug() << "Enemigo creado con posición:" << enemigo1->pos() << "y data(0):" << enemigo1->data(0).toString();
    Enemigo* enemigo2 = new Enemigo(QPoint(782, 468), 2, 0, 318, 0.3, 48);
    enemigo2->setData(0, "enemigo");
    scene->addItem(enemigo2);
    qDebug() << "Enemigo creado con posición:" << enemigo2->pos() << "y data(0):" << enemigo2->data(0).toString();
    Enemigo* enemigo3 = new Enemigo(QPoint(1182, 369), 2, 1, 605, 0.3, 48);
    enemigo3->setData(0, "enemigo");
    scene->addItem(enemigo3);
    qDebug() << "Enemigo creado con posición:" << enemigo3->pos() << "y data(0):" << enemigo3->data(0).toString();
    Enemigo* enemigo4 = new Enemigo(QPoint(1580, 468), 2, 0, 0, 6.3, 35);
    enemigo4->setData(0, "enemigo");
    scene->addItem(enemigo4);
    qDebug() << "Enemigo creado con posición:" << enemigo4->pos() << "y data(0):" << enemigo4->data(0).toString();
}

void Enemigo::cambiarSprite(){
    columna += ancho;
    if(columna >= columnaInicial + (210)){
        columna = columnaInicial;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}
