#include "menu.h"

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

void Menu::conectarBotones() {
    connect(vista->botonNivel1, &QPushButton::clicked, this, &Menu::nivel1);
    connect(vista->botonNivel2, &QPushButton::clicked, this, &Menu::nivel2);
    connect(vista->botonNivel1, &QPushButton::clicked, this, &Menu::salir);
}

void Menu::nivel1()
{
    /*
    escena = new QGraphicsScene;
    menu = new QGraphicsPixmapItem(QPixmap(":/sprites/MenuPrincipal.png"));
    escena->addItem(menu);
    vista->graphicsView->setScene(escena);
*/
}

void Menu::nivel2()
{

}

void Menu::salir()
{

}
