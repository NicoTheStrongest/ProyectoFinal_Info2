#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : personaje{parent}
{}

Jugador::Jugador(QGraphicsScene *escena, int nivel)
    : direccionActual(2), velocidad(2), puntos(0), vida(100), nivelActual(nivel){
    personaje::setEscenario(escena);
    //HITBOX
    setRect(0, 0, 44, 64);
    pixmap = new QPixmap(":/sprites/Homer.png");

    //CONNECTS DE TIMERS
    mover = new QTimer(); //->APLICAR GRAVEDAD (LVL 2)
    connect(mover, SIGNAL(timeout()), this, SLOT(aplicarGravedad()));
    sprite = new QTimer(); //->MANEJO DE SPRITES
    connect(sprite, SIGNAL(timeout()), this, SLOT(cambiarSprite()));

    //POSICIONES INICIALES
    if (nivelActual == 1){
        posicion = QPoint(20, 370); //POSICION INICIAL (LVL 1)
    }
    else if (nivelActual == 2){
        posicion = QPoint(660, 463); //POSICION INICIAL (LVL 1)
        mover->start(50);
        ultimaDireccionX = "";
    }
    setPos(posicion);

    //MANEJO DE SPRITES
    filas = 15;
    columnas = 83;
    ancho = 44;
    alto = 64;
    QColor colorVerde(25, 255, 95);
    pixmap->setMask(pixmap->createMaskFromColor(colorVerde.rgb(), Qt::MaskInColor));
    sprite->start(300);
}

//-------------------GETTERS--------------------------
QPoint Jugador::getPosicion() const {return posicion;}
short int Jugador::getPuntos() const {return puntos;}
short int Jugador::getVida() const {return vida;}
bool Jugador::getControl() const {return control;}
int Jugador:: getNivelActual() const {return nivelActual;}

//-------------------METODOS--------------------------
void Jugador::saltar(){
    if(posicion.y() - 20 > 340){
        posicion.setY(posicion.y() - 20);
        setPos(posicion);
    }
}

void Jugador::cargarPersonaje(QGraphicsScene *scene){
    scene->addItem(this);
    setPos(posicion);
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

void Jugador::moverAbajo(){
    if(posicion.y() + velocidad < 480){
        posicion.setY(posicion.y() + velocidad);
        setPos(posicion);
        direccionActual = 0;
        qDebug() << "Moviendo abajo, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
    }
}

QRectF Jugador::boundingRect() const{
    return QRectF(0,0,ancho,alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0,0,*pixmap,columnas,filas,ancho, alto);
}

void Jugador::keyPressEvent(QKeyEvent *event){
    qDebug() << "tecla presionada desde jugador";
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
    default:
        break;
    }
    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    //qDebug() << "Cantidad de colisiones detectadas:" << colisiones.size();
    for (QGraphicsItem* item : colisiones) {
        //qDebug() << "Elemento en colisión, data(0):" << item->data(0).toString();
        if (item->data(0).toString() == "basura") {
            qDebug() << "colision basura";
            if(item->data(1).toBool() == false){
                item->setOpacity(0);
                item->setData(1,true);
                aumentarPuntos();
                break;
            }
        }
        else if(item->data(0).toString() == "enemigo"){
            qDebug() << "colision enemigo";
            if((posicion.y() - (velocidad * 6) < 340) || (posicion.y() - (velocidad * 6) > 480)){
                posicion.setX(posicion.x() - velocidad * 6);
                setPos(posicion);
            }
            else{
                posicion.setY(posicion.y() - velocidad * 6);
                posicion.setX(posicion.x() - velocidad * 6);
                setPos(posicion);
            }
            disminuirVida();
            break;
        }
    }
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
    if(nivelActual == 1){
        if(posicion.x() >= 1852 && puntos == 100){
            return true;
        }
        else if(vida <= 0){
            return true;
        }
        return false;
    }
    else if(nivelActual == 2){
        if(posicion.x() <= 295 && posicion.y() <= 295){
            return true;
        }
        else if(vida <= 0){
            return true;
        }
        return false;
    }
    return false;
}

void Jugador::movimientoNivel2(QKeyEvent *event){
    int nuevaX = x();
    int viejaX = x();
    int viejaY = y();
    // Verificar las cuatro esquinas del personaje
    switch(event->key()){
    case Qt::Key_Left:
    case  Qt::Key_A:
    {
        ultimaDireccionX = "izquierda";
        nuevaX = x() - velocidad;
        qDebug()<<"izquierda";
        //posicion.setX(posicion.x() - velocidad);
        //moverAtras();
        qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:
    {
        ultimaDireccionX = "derecha";
        nuevaX = x() + velocidad;
        qDebug()<<"derecha";
        //posicion.setX(posicion.x() + velocidad);
        //moverAdelante();
        qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
        break;
    }
    case Qt::Key_Up:
    case Qt::Key_W:
    {
        if(colision){
            ultimaDireccionX = "arriba";
            velocidadSalto = -12;
            qDebug()<<"salta";
        }
        //posicion.setY(posicion.y() - 6);
        //moverArriba();
        qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S:
    {
        //nuevaY = y() + velocidad;
        //posicion.setY(posicion.y() + velocidad);
        //moverAbajo();
        qDebug() << "Moviendo adelante, nueva posicion X:" << posicion.x() << "Nueva posicion Y:" << posicion.y();
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
    posicion.setX(nuevaX);
    setPos(posicion);

    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    //qDebug() << "Cantidad de colisiones detectadas:" << colisiones.size();
    for (QGraphicsItem* item : colisiones) {
        //qDebug() << "Elemento en colisión, data(0):" << item->data(0).toString();
        if (item->data(0).toString() == "plataforma") {
            objetoFisico.setTiempo(0.0);
            velocidadSalto = 0;
            if(ultimaDireccionX == "derecha"){posicion.setX(viejaX-1);}
            if(ultimaDireccionX == "izquierda"){posicion.setX(viejaX+1);}
            posicion.setY(viejaY);
            setPos(posicion);
            colision = true;
            qDebug()<<"colision";
        }
        if(item->data(0).toString() == "enemigo"){
            if(item->data(1).toBool() == false){
                item->setOpacity(0);
                item->setData(1,true);
                qDebug() << "colision enemigo";
                disminuirVida();
            }
        }
        if(item->data(0).toString() == "sierra"){
            posicion.setX(660);
            posicion.setY(463);
            setPos(posicion);
            disminuirVida();
            qDebug()<<"navajazo";
        }
        else{colision = false;}
        return;
    }
}


//-------------------SLOTS--------------------------
void Jugador::cambiarSprite(){
    columnas += 44;
    if(columnas>=435){
        columnas = 83;
    }
    this->update(0,0,ancho,alto);
}

void Jugador::aplicarGravedad(){
    int viejaX = x();
    int viejaY = y();
    objetoFisico.aplicarGravedad(posicion, velocidadSalto);
    setPos(posicion);
    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    //qDebug() << "Cantidad de colisiones detectadas:" << colisiones.size();
    for (QGraphicsItem* item : colisiones) {
        //qDebug() << "Elemento en colisión, data(0):" << item->data(0).toString();
        if (item->data(0).toString() == "plataforma") {
            objetoFisico.setTiempo(0.0);
            velocidadSalto = 0;
            posicion.setX(viejaX);
            posicion.setY(viejaY);
            //if(ultimaDireccionX == "arriba"){posicion.setY(viejaY+1);}
            //else{posicion.setY(viejaY);}
            setPos(posicion);
            colision = true;
            //qDebug()<<"colision";
        }
        if(item->data(0).toString() == "enemigo"){
            if(item->data(1).toBool() == false){
                item->setOpacity(0);
                //this->escenario->removeItem(item);
                item->setData(1,true);
                disminuirVida();
                qDebug() << "colision enemigo";
            }
        }
        if(item->data(0).toString() == "sierra"){
            posicion.setX(660);
            posicion.setY(463);
            setPos(posicion);
            disminuirVida();
            qDebug()<<"navajazo";
        }
        return;
    }
}











