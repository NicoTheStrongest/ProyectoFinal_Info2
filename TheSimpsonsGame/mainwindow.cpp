#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

















