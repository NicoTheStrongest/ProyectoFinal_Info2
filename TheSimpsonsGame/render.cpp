#include "render.h"

Render::Render(QObject *parent)
    : QObject{parent}
{}

Render::Render(Ui::MainWindow *ui) : vista(ui)
{
    escena = new QGraphicsScene;
    fondo = new QGraphicsPixmapItem(QPixmap(":/sprites/MenuPrincipal.png"));
    escena->addItem(fondo);
    vista->graphicsView->setScene(escena);
}

void Render::cargarEscenaNivel1()
{
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
    //Añadimos obstaculos
    //añadirObstaculos();
    //añadirEnemigos
    //añadirEnemigos();
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Render::añadirBasura()
{
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
void Render::añadirEnemigos()
{
    /*
    QString enemigo1 = "";
    QString enemigo1 = "";
    QString enemigo1 = "";
    QString enemigo1 = "";
    */
    QPixmap basuraPixmap(":/sprites/Bassura.png");
    QPixmap scaledBasuraPixmap = basuraPixmap.scaled(40, 40, Qt::KeepAspectRatio);

    for (int i = 0; i < 4; ++i) {
        QGraphicsPixmapItem *basuraItem = new QGraphicsPixmapItem(scaledBasuraPixmap);
        if(i%2==0){basuraItem->setPos(400 * (i+1), 453);}
        else{basuraItem->setPos(400 * (i+1), 372);}
        escena->addItem(basuraItem);
    }
}

void Render::cargarEscenaNivel2()
{
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    escena = new QGraphicsScene;
    fondo = new QGraphicsPixmapItem(QPixmap(":/sprites/Escenario2.jpeg").scaled(1000, 1000, Qt::KeepAspectRatio));
    escena->addItem(fondo);
    vista->graphicsView->setScene(escena);
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void Render::mostrarMensajeFinal(short int vida, QPoint posicion){
    QGraphicsPixmapItem* mensajeFinal;
    if(vida <= 0){
        QPixmap pixmap(":/sprites/GameOver.png");
        pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio);
        mensajeFinal = new QGraphicsPixmapItem(pixmap);
    }
    else if(posicion.x() >= 1852){
        QPixmap pixmap(":/sprites/LevelCompleted.png");
        pixmap = pixmap.scaled(400, 400, Qt::KeepAspectRatio);
        mensajeFinal = new QGraphicsPixmapItem(pixmap);
    }
    mensajeFinal->setPos((escena->width() - mensajeFinal->pixmap().width()) / 2, (escena->height() - mensajeFinal->pixmap().height()) / 2);
    escena->addItem(mensajeFinal);
    vista->graphicsView->centerOn(mensajeFinal);
}








