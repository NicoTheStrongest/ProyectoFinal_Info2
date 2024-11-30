#include "render.h"
#include <QGraphicsProxyWidget>
#include <QPushButton>

Render::Render(QObject *parent)
    : QObject{parent}
{}

Render::Render(Ui::MainWindow *ui) : vista(ui){
    escena = new QGraphicsScene;
    fondo = new QGraphicsPixmapItem(QPixmap(":/sprites/MenuPrincipal.png"));
    escena->addItem(fondo);
    vista->graphicsView->setScene(escena);
    vista->botonAtras->setVisible(false);
}

void Render::cargarEscenaNivel1(){
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    escena = new QGraphicsScene;
    vista->graphicsView->setScene(escena);
    //añadimos fondo
    fondo = new QGraphicsPixmapItem(QPixmap(":/sprites/Springfield2.png"));
    escena->addItem(fondo);
    //añadimos basura
    añadirBasura();
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Render::añadirBasura(){
    QPixmap basuraPixmap(":/sprites/Bassura.png");
    QPixmap scaledBasuraPixmap = basuraPixmap.scaled(40, 40, Qt::KeepAspectRatio);

    for (int i = 0; i < 4; ++i) {
        QGraphicsPixmapItem *basuraItem = new QGraphicsPixmapItem(scaledBasuraPixmap);
        if(i%2==0){basuraItem->setPos(400 * (i+1), 453);}
        else{basuraItem->setPos(400 * (i+1), 372);}
        escena->addItem(basuraItem);
        basuraItem->setData(0, "basura");
    }
}

/*
void Render::añadirObstaculos(){
    QPixmap obstaculoPixmap(":/sprites/obstaculoMadera.png");
    QPixmap scaledObstaculoPixmap = obstaculoPixmap.scaled(50, 100, Qt::KeepAspectRatio);
    QVector<QPoint> posiciones = {QPoint(580, 380), QPoint(986, 380), QPoint(1400, 386)};
    for (const QPoint &pos : posiciones){
        QGraphicsPixmapItem *obstaculoItem = new QGraphicsPixmapItem(scaledObstaculoPixmap);
        obstaculoItem->setPos(pos);
        escena->addItem(obstaculoItem);
        obstaculoItem->setData(0,"obstaculo");
    }
}
*/

void Render::cargarEscenaNivel2(){
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    escena = new QGraphicsScene;
    fondo = new QGraphicsPixmapItem(QPixmap(":/sprites/Escenario2.jpeg"));
    escena->addItem(fondo);
    añadirPlataformas();
    vista->graphicsView->setScene(escena);
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void Render::añadirPlataformas(){
    QList<QRect> areasOcupadas = {
        QRect(100, 543, 680, 20),
        QRect(220, 440, 560, 20),
        QRect(100, 340, 20, 223),
        QRect(120, 340, 380, 20),
        QRect(220, 340, 460, 20),
        QRect(780, 220, 20, 343),
        QRect(200, 220, 580, 20),
        QRect(200, 220, 20, 120)
    };

    for (const QRect& area : areasOcupadas) {
        dibujarPared(area.x(), area.y(), area.width(), area.height(),QColorConstants::Black);
    }
}

void Render:: dibujarPared(int x, int y, int ancho, int alto, QColor color) {
    QGraphicsRectItem* pared = new QGraphicsRectItem(x, y, ancho, alto);
    pared->setBrush(QBrush(QColor(color)));
    escena->addItem(pared);
    pared->setData(0, "plataforma");
}

void Render::volverAlMenuPrincipal(){
    if (escena) {
        escena->clear();
        qDebug() << "escena limpia";
    }
    escena = new QGraphicsScene;
    fondo = new QGraphicsPixmapItem(QPixmap(":/sprites/MenuPrincipal.png"));
    escena->addItem(fondo);
    vista->graphicsView->setScene(escena);
    vista->botonNivel1->setVisible(true);
    vista->botonNivel2->setVisible(true);
    vista->botonSalir->setVisible(true);
    vista->botonAtras->setVisible(false);
    qDebug() << "De vuelta en el menu principal";
}

void Render::mostrarMensajeFinal(short int vida, QPoint posicion){
    QGraphicsPixmapItem* mensajeFinal;
    QPixmap pixmapVolver(":/sprites/Atras.png");
    QGraphicsPixmapItem* volver = new QGraphicsPixmapItem(pixmapVolver);
    if(vida <= 0){
        qDebug() << "Nivel perdido";
        QPixmap pixmap(":/sprites/GameOver.png");
        pixmap = pixmap.scaled(300, 300, Qt::KeepAspectRatio);
        mensajeFinal = new QGraphicsPixmapItem(pixmap);
    }
    else if(posicion.x() >= 1852 && posicion.y() >= 340 && posicion.y() <= 480){
        qDebug() << "Nivel completo";
        QPixmap pixmap(":/sprites/LevelCompleted.png");
        pixmap = pixmap.scaled(300, 300, Qt::KeepAspectRatio);
        mensajeFinal = new QGraphicsPixmapItem(pixmap);
    }

    mensajeFinal->setPos((escena->width() - mensajeFinal->pixmap().width()) / 2, (escena->height() - mensajeFinal->pixmap().height()) / 2);

    int mensajeFinalX = (escena->width() - mensajeFinal->pixmap().width()) / 2;
    int mensajeFinalY = (escena->height() - mensajeFinal->pixmap().height()) / 2;
    volver->setPos(mensajeFinalX + (mensajeFinal->pixmap().width() - volver->pixmap().width()) / 2, mensajeFinalY + mensajeFinal->pixmap().height() + 20);

    //vista->botonAtras->setGeometry(volver->x(), volver->y(), volver->pixmap().width(), volver->pixmap().height());
    vista->botonAtras->setVisible(true);
    qDebug() << "boton agregado a la escena" << "posicion " << vista->botonAtras->pos();

    escena->addItem(mensajeFinal);
    escena->addItem(volver);
    vista->graphicsView->centerOn(mensajeFinal);
}








