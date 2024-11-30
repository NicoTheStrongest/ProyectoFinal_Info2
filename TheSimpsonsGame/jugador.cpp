#include "jugador.h"

Jugador::Jugador(QObject *parent)
    : personaje{parent}
{}

Jugador::Jugador(QGraphicsScene *escena)
    : direccionActual(2), velocidad(2), puntos(0), vida(100), control(true)
{
    personaje::setEscenario(escena);
    setRect(0, 0, 44, 64);
    //setBrush(QBrush(Qt::yellow));
    //setFlag(QGraphicsItem::ItemIsFocusable);
    //setFocus();

    mover = new QTimer();
    connect(mover, SIGNAL(timeout()), this, SLOT(aplicarGravedad()));

    nivelActual = 2;
    if (nivelActual == 1){
        posicion = QPoint(20, 370);
        pixmap = new QPixmap(":/sprites/Homer.png");
    }
    else if (nivelActual == 2){
        posicion = QPoint(660, 460);
        pixmap = new QPixmap(":/sprites/Homer.png");
        mover->start(60);
    }
    setPos(posicion);

    sprite = new QTimer();
    connect(sprite, SIGNAL(timeout()), this, SLOT(cambiarSprite()));
    sprite->start(300);

    filas = 15;
    columnas = 83;
    QColor colorVerde(25, 255, 95);
    pixmap->setMask(pixmap->createMaskFromColor(colorVerde.rgb(), Qt::MaskInColor));
    ancho = 44;
    alto = 64;
}

QPoint Jugador::getPosicion() const {return posicion;}
short int Jugador::getPuntos() const {return puntos;}
short int Jugador::getVida() const {return vida;}
bool Jugador::getControl() const {return control;}
int Jugador:: getNivelActual() const {return nivelActual;}
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

void Jugador::cambiarSprite(){
    columnas += 44;
    if(columnas>=435){
        columnas = 83;
    }
    this->update(0,0,ancho,alto);
}

void Jugador::parar(){
    control = false;
}

void Jugador::keyPressEvent(QKeyEvent *event){
    qDebug() << "tecla presionada desde jugador";
    if (event->key() == Qt::Key_Escape) {
        event->ignore();
        return;
    }

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
    if(posicion.x() >= 1852 && puntos == 100){
        return true;
    }
    else if(vida <= 0){
        return true;
    }
    return false;
}

void Jugador::movimientoNivel2(QKeyEvent *event){
    int nuevaX = x();
    int nuevaY = y();
    int viejaX = x();
    int viejaY = y();
    // Verificar las cuatro esquinas del personaje
    switch(event->key()){
    case Qt::Key_Left:
    case  Qt::Key_A:
    {
        nuevaX = x() - velocidad;
        //posicion.setX(posicion.x() - velocidad);
        //moverAtras();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:
    {
        nuevaX = x() + velocidad;
        //posicion.setX(posicion.x() + velocidad);
        //moverAdelante();
        break;
    }
    case Qt::Key_Up:
    case Qt::Key_W:
    {
        if(!colision){nuevaY = y() -10;}
        //posicion.setY(posicion.y() - 6);
        //moverArriba();
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S:
    {
        nuevaY = y() + velocidad;
        //posicion.setY(posicion.y() + velocidad);
        //moverAbajo();
        break;
    }
    case Qt::Key_Space:
    {
        //saltar();
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
    posicion.setY(nuevaY);

    setPos(posicion);

    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    //qDebug() << "Cantidad de colisiones detectadas:" << colisiones.size();
    for (QGraphicsItem* item : colisiones) {
        //qDebug() << "Elemento en colisión, data(0):" << item->data(0).toString();
        if (item->data(0).toString() == "plataforma") {
            posicion.setX(viejaX);
            posicion.setY(viejaY);
            setPos(posicion);
            colision = true;
            qDebug()<<"colision";
            return;
        }
    }
    colision = false;
}

void Jugador::aplicarGravedad(){
    int viejaX = x();
    int viejaY = y();
    objetoFisico.aplicarGravedad(posicion, velocidad);
    setPos(posicion);
    // Verificar si colisiona con algún objeto etiquetado como "pared"
    QList<QGraphicsItem*> colisiones = collidingItems();
    //qDebug() << "Cantidad de colisiones detectadas:" << colisiones.size();
    for (QGraphicsItem* item : colisiones) {
        //qDebug() << "Elemento en colisión, data(0):" << item->data(0).toString();
        if (item->data(0).toString() == "plataforma") {
            posicion.setX(viejaX);
            posicion.setY(viejaY);
            setPos(posicion);
            colision = true;
            qDebug()<<"colision";
            return;
        }
    }
    colision = false;
    qDebug() << "aplicando gravedad";
}




















