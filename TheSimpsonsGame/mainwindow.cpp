#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personaje.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //---------------------------------------//
    //      Añadir elementos a la escena
    //---------------------------------------//
    interfazPrincipal = new Menu(ui);
    interfazPrincipal->conectarBotones();
    //---------------------------------------//
    ui->graphicsView->setFocus();
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

















