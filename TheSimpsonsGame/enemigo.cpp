#include "enemigo.h"

Enemigo::Enemigo(QObject *parent)
    : personaje{parent}
{}

//CONTRUCTOR (LVL 1)
Enemigo::Enemigo(QPoint posicionInicial, int velocidad, int direccionActual, float columnaInicial, float fila, float ancho, float alto, short int nivel)
    :posicion(posicionInicial), velocidad(velocidad), direccionActual(direccionActual), columnaInicial(columnaInicial), fila(fila), ancho(ancho), alto(alto)
{
    setPos(posicion);
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);
    lanzamiento = new QTimer(this);
    if (nivel == 1){
        sprite = new QPixmap(":/sprites/NPC1.png");
        QColor colorAzul(151,198,222,255);
        sprite->setMask(sprite->createMaskFromColor(colorAzul.rgb(), Qt::MaskInColor));
        connect(timer, SIGNAL(timeout()), this, SLOT(moverNivel1()));

    }
    else if(nivel == 2){
       sprite = new QPixmap(":/sprites/NPC2.png");
       QColor colorAzulito(86,177,222,255);
       sprite->setMask(sprite->createMaskFromColor(colorAzulito.rgb(), Qt::MaskInColor));
       connect(timer2, SIGNAL(timeout()), this, SLOT(moverNivel2()));
       connect(lanzamiento, SIGNAL(timeout()), this, SLOT(lanzarAntorcha()));
       connect(timer3,SIGNAL(timeout()), this, SLOT(moverAntorchas()));
       timer2->start(300);
       timer3->start(40);
       lanzamiento->start(5);
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(cambiarSprite()));
    timer->start(500);
}

//-------------------METODOS--------------------------
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

void Enemigo::moverNivel2(){
    int nuevaX = posicion.x();
    int nuevaY = posicion.y();
    limiteIzquierda = 212;
    limiteDerecha = 756;

    if(direccionActual == 2){
        nuevaX += velocidad;
        if(nuevaX >= limiteDerecha){
            nuevaX = limiteDerecha;
            direccionActual = 3;
        }
    }
    else{
        nuevaX -= velocidad;
        if(nuevaX <= limiteIzquierda){
            nuevaX = limiteIzquierda;
            direccionActual = 2;
        }
    }
    posicion.setX(nuevaX);

    QList<QGraphicsItem*> colisiones = collidingItems();
    bool sobrePlataforma = false;
    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "plataforma") {
            sobrePlataforma = true;
            break;
        }
    }
    if(!sobrePlataforma){
       objetoFisico.aplicarGravedad(posicion, velocidad);
    }
    else{
        posicion.setY(nuevaY);
    }
    setPos(posicion);
    //qDebug() << "Enemigo movido a X:" << posicion.x() << "Y:" << posicion.y();
}

void Enemigo::lanzarAntorcha(){
    if (antorchas.size() >= 1) {return;}
    QPixmap antorcha(":/sprites/antorcha.png");
    QPixmap scaledAntorcha = antorcha.scaled(60, 40, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *antorchaItem = new QGraphicsPixmapItem(scaledAntorcha);
    antorchaItem->setPos(this->posicion.x(), this->posicion.y());
    this->scene()->addItem(antorchaItem);
    antorchaItem->setData(0, "enemigo");
    antorchas.append(antorchaItem);
}

void Enemigo::moverAntorchas(){
    for(int i = 0; i < antorchas.size(); i++){
        QGraphicsPixmapItem* antorcha = antorchas[i];
        QPoint posicionAct = QPoint(antorcha->pos().x(), antorcha->pos().y());
        objetoFisico.aplicarGravedad(posicionAct,0);
        antorcha->setPos(posicionAct);
        if(antorcha->pos().y() >= 530){
            scene()->removeItem(antorcha);
            delete antorcha;
            antorchas.removeAt(i);
            i--;
        }
    }
}

void Enemigo::cargarEnemigosNivel1(QGraphicsScene *scene){
    Enemigo* enemigo1 = new Enemigo(QPoint(380, 369), 2, 1, 0, 0.3, 44, 85, 1);
    enemigo1->setData(0, "enemigo");
    scene->addItem(enemigo1);
    qDebug() << "Enemigo creado con posición:" << enemigo1->pos() << "y data(0):" << enemigo1->data(0).toString();
    Enemigo* enemigo2 = new Enemigo(QPoint(782, 468), 2, 0, 318, 0.3, 48, 85, 1);
    enemigo2->setData(0, "enemigo");
    scene->addItem(enemigo2);
    qDebug() << "Enemigo creado con posición:" << enemigo2->pos() << "y data(0):" << enemigo2->data(0).toString();
    Enemigo* enemigo3 = new Enemigo(QPoint(1182, 369), 2, 1, 605, 0.3, 48, 85, 1);
    enemigo3->setData(0, "enemigo");
    scene->addItem(enemigo3);
    qDebug() << "Enemigo creado con posición:" << enemigo3->pos() << "y data(0):" << enemigo3->data(0).toString();
    Enemigo* enemigo4 = new Enemigo(QPoint(1580, 468), 2, 0, 0, 6.3, 35, 85, 1);
    enemigo4->setData(0, "enemigo");
    scene->addItem(enemigo4);
    qDebug() << "Enemigo creado con posición:" << enemigo4->pos() << "y data(0):" << enemigo4->data(0).toString();
}


void Enemigo::cargarEnemigosNivel2(QGraphicsScene *scene){
    Enemigo* enemigo5 = new Enemigo(QPoint(212, 187), 7, 2, 0, 9.15, 43.1, 76, 2);
    enemigo5->setData(0, "enemigo");
    scene->addItem(enemigo5);
    qDebug() << "Enemigo creado con posición:" << enemigo5->pos() << "y data(0):" << enemigo5->data(0).toString();
    Enemigo* enemigo6 = new Enemigo(QPoint(734, 187), 7, 2, 0, 3.55, 35, 76, 2);
    enemigo6->setData(0, "enemigo");
    scene->addItem(enemigo6);
    qDebug() << "Enemigo creado con posición:" << enemigo6->pos() << "y data(0):" << enemigo6->data(0).toString();
}

void Enemigo::cargarEnemigosSierra1(QGraphicsScene *scene, int posX, int posY){
    moverSierra = new QTimer(this);
    connect(moverSierra, SIGNAL(timeout()), this, SLOT(movimientoSierra()));

    //sierra 1
    QPixmap sierraPixmap(":/sprites/Sierra.png");
    QPixmap scaledsierraPixmap = sierraPixmap.scaled(40, 40, Qt::KeepAspectRatio);
    sierraItem = new QGraphicsPixmapItem(scaledsierraPixmap);
    scene->addItem(sierraItem);
    sierraItem->setData(0,"sierra");
    objetoFisico.inicializarMovimientoCircular(posX, posY, 50, 5, 6, 0, 0);
    rotacionSierra = 0;
    sierraItem->setTransformOriginPoint(boundingRect().center());
}

void Enemigo::cargarEnemigosSierra2(QGraphicsScene *scene, int posX, int posY){
    moverSierra = new QTimer(this);
    connect(moverSierra, SIGNAL(timeout()), this, SLOT(movimientoSierra()));

    //sierra 1
    QPixmap sierraPixmap(":/sprites/Sierra.png");
    QPixmap scaledsierraPixmap = sierraPixmap.scaled(40, 40, Qt::KeepAspectRatio);
    sierraItem = new QGraphicsPixmapItem(scaledsierraPixmap);
    scene->addItem(sierraItem);
    sierraItem->setData(0,"sierra");
    objetoFisico.inicializarMovimientoCircular(posX, posY, 50, 5, 6, 0, 0);
    rotacionSierra = 0;
    sierraItem->setTransformOriginPoint(boundingRect().center());
}

void Enemigo::iniciarRotacion(){moverSierra->start(16);}
void Enemigo::detenerRotacion(){moverSierra->stop();}

QRectF Enemigo::boundingRect() const{
    return QRectF(-ancho / 2, -alto / 2, ancho, alto);
}

QPainterPath Enemigo::shape() const {
    QPainterPath rectangulo;
    rectangulo.addRect(boundingRect());
    return rectangulo;
}

void Enemigo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    float filaInicial = fila * alto;
    painter->drawPixmap(-ancho / 2, -alto / 2, *sprite , columna, filaInicial, ancho, alto);
}

//-------------------SLOTS--------------------------

void Enemigo::moverNivel1(){
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

void Enemigo::cambiarSprite(){
    columna += ancho;
    if(columna >= columnaInicial + (210)){
        columna = columnaInicial;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

void Enemigo::movimientoSierra(){
    //sierra 1
    objetoFisico.aplicarMovimientocircular(posicionSierra, rotacionSierra);
    this->sierraItem->setPos(posicionSierra);
    this->sierraItem->setRotation(rotacionSierra);
}























