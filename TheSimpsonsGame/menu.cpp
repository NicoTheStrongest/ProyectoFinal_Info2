#include "menu.h"
#include <QApplication>

Menu::Menu(QObject *parent)
    : QObject{parent}
{}

Menu::Menu(Ui::MainWindow *ui) : vista(ui)
{    
    escena = new QGraphicsScene;
    menu = new QGraphicsPixmapItem(QPixmap(":/sprites/MenuPrincipal.png"));
    escena->addItem(menu);
    vista->graphicsView->setScene(escena);
}

void Menu::cargarEscenaNivel1()
{
    vista->botonNivel1->setVisible(false);
    vista->botonNivel2->setVisible(false);
    vista->botonSalir->setVisible(false);
    escena = new QGraphicsScene;
    menu = new QGraphicsPixmapItem(QPixmap(":/sprites/Springfield2.png"));
    escena->addItem(menu);
    vista->graphicsView->setScene(escena);
    vista->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    vista->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
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
