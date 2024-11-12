#include "menu.h"
#include "jugador.h"
#include "ui_mainwindow.h"
#include <QApplication>

Menu::Menu(QObject *parent)
    : QObject{parent}
{}

Menu::Menu(Ui::MainWindow *ui) : vista(ui)
{    
    escena = new QGraphicsScene;
    menu = new QGraphicsPixmapItem(QPixmap(":/sprites/MenuPrincipal.png"));
    jugador = new Jugador();
    escena->addItem(jugador);
    escena->addItem(menu);
    vista->graphicsView->setScene(escena);
    jugador->setFocus();
    vista->graphicsView->setFocus();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarJuego()));
    timer->start(16);
}

void Menu::cargarEscenaNivel1()
{
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    escena = new QGraphicsScene;
    menu = new QGraphicsPixmapItem(QPixmap(":/sprites/Springfield2.png"));
    escena->addItem(menu);
    jugador->cargarPersonaje(escena);
    jugador->setFocus();
    vista->graphicsView->setScene(escena);
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    timer->start(16);
}

void Menu::cargarEscenaNivel2()
{
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    escena = new QGraphicsScene;
    menu = new QGraphicsPixmapItem(QPixmap(":/sprites/Escenario2.jpeg").scaled(1000, 1000, Qt::KeepAspectRatio));
    escena->addItem(menu);
    vista->graphicsView->setScene(escena);
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
void Menu::actualizarJuego(){
    jugador->moverEndireccionActual();
}
void Menu::keyPressEvent(QKeyEvent *event){
    jugador->keyPressEvent(event);
}
/*
void Menu::salir()
{
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    //qDebug() << "Se presionó ESC. Cerrando la aplicación...";
    QApplication::quit();  // Cerrar la aplicación
}
*/
