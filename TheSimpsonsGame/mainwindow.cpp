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
    renderEscena();
    //---------------------------------------//
    ui->graphicsView->setFocus();
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete interfazPrincipal;
    delete ui;
}

void MainWindow::renderEscena()
{
    connect(ui->botonNivel1, &QPushButton::clicked, this, &MainWindow::nivel1);
    connect(ui->botonNivel2, &QPushButton::clicked, this, &MainWindow::nivel2);
    connect(ui->botonSalir, &QPushButton::clicked, this, [](){
        qDebug() << "Botón salir presionado";
        QApplication::quit();
    });
}

void MainWindow::nivel1()
{
    interfazPrincipal->cargarEscenaNivel1();
}

void MainWindow::nivel2()
{
    interfazPrincipal->cargarEscenaNivel2();
}

















