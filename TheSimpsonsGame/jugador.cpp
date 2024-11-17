#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : personaje{parent}
{}

Jugador::Jugador(QGraphicsScene *escena)
    : direccionActual(2), velocidad(2), posicion(20, 370), puntos(0), vida(100), control(true)
{
    personaje::setEscenario(escena);
    setRect(0, 0, 44, 85);
    //setBrush(QBrush(Qt::yellow));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setPos(posicion);

    sprite = new QTimer();
    connect(sprite, SIGNAL(timeout()), this, SLOT(cambiarSprite()));
    sprite->start(500);
    filas = 0;
    columnas = 83;
    pixmap = new QPixmap(":/sprites/Homer.png");
    QColor colorVerde(25, 255, 95);
    pixmap->setMask(pixmap->createMaskFromColor(colorVerde.rgb(), Qt::MaskInColor));
    ancho = 44;
    alto = 85;
}

QPoint Jugador::getPosicion() const {return posicion;}
short int Jugador::getPuntos() const {return puntos;}
short int Jugador::getVida() const {return vida;}
bool Jugador::getControl() const {return control;}
void Jugador::cargarPersonaje(QGraphicsScene *scene){
    scene->addItem(this);
    setPos(posicion);
}

void Jugador::saltar(){
    if(posicion.y() - 20 > 340){
        posicion.setY(posicion.y() - 20);
        setPos(posicion);
    }
}

void Jugador::moverAdelante(){
    if(posicion.x() + velocidad < 1854){
        posicion.setX(posicion.x() + velocidad);
        setPos(posicion);
        direccionActual = 0;
        qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
    }
}

void Jugador::moverAtras(){
    if(posicion.x() - velocidad > 0){
        posicion.setX(posicion.x() - velocidad);
        setPos(posicion);
        direccionActual = 1;
        qDebug() << "Moviendo atrás, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
    }
}

void Jugador::moverArriba()
{
    if(posicion.y() - velocidad > 340){
        posicion.setY(posicion.y() - velocidad);
        setPos(posicion);
        direccionActual = 0;
        qDebug() << "Moviendo arriba, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
    }
}

void Jugador::moverAbajo()
{
    if(posicion.y() + velocidad < 480){
        posicion.setY(posicion.y() + velocidad);
        setPos(posicion);
        direccionActual = 0;
        qDebug() << "Moviendo abajo, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
    }
}

QRectF Jugador::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,0,ancho, alto);
}



void Jugador::cambiarSprite()
{
    columnas += 44;
    if(columnas>=435){
        columnas = 83;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

void Jugador::parar(){
    control = false;
}

void Jugador::keyPressEvent(QKeyEvent *event){
    if(!getControl()){return;}
    switch(event->key()){
    case Qt::Key_Left:
    case  Qt::Key_A:
    {
        moverAtras();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:
    {
        moverAdelante();
        break;
    }
    case Qt::Key_Up:
    case Qt::Key_W:
    {
        moverArriba();
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S:
    {
        moverAbajo();
        break;
    }
    case Qt::Key_Space:
    {
        saltar();
        break;
    }
    case Qt::Key_Escape:
    {
        //Aca se puede poner tambien el menu de opciones para volver o continuar

        qDebug() << "Se presionó ESC. Cerrando la aplicación...";
        QApplication::quit();  // Cerrar la aplicación
    }
        return;
    default:
        break;
    }

    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();

    for (QGraphicsItem* item : colisiones) {
        if (item->data(0).toString() == "basura") {
            if(item->data(1).toBool() == false){
                item->setOpacity(0); // se hacen visibles las pareced
                item->setData(1,true);
                aumentarPuntos();
                break;
            }
        }
        else if(item->data(0).toString() == "enemigo"){
            posicion.setY(posicion.y() - velocidad * 4);
            posicion.setX(posicion.x() - velocidad * 4);
            setPos(posicion);
            disminuirVida();
            break;
        }
    }

    /*
    // Si colisiona con una pared, revertir el movimiento
    if (colisionConPared) {
        qDebug() << "Colisión detectada con una pared";
        setPos(pos_original);  // Revertir el movimiento

    } else {
        // No hay colisión, permitir el movimiento
        cambiarSprite();
    }
    */
}

void Jugador::aumentarPuntos(){
    puntos += 25;
    emit puntajeCambiado(puntos);
}

void Jugador::disminuirVida(){
    if (vida > 0){
        vida -= 10;
        emit vidaCambio(vida);
    }
}

bool Jugador::finalizarNivel(){
    if(posicion.x() >= 1852 && puntos == 100){
        return true;
    }
    else if(vida <= 0){
        return true;
    }
    return false;
}
