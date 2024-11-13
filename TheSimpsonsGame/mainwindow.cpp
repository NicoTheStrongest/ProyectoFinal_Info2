#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarVista()));
    //Conectar botones y crear render para manipulacion de escenarios
    interfazPrincipal = new Render(ui);
    conectarBotones();
    ui->graphicsView->setFocus();
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete interfazPrincipal;
    delete ui;
}

void MainWindow::actualizarVista(){
    ui->graphicsView->centerOn(jugador);
}

void MainWindow::conectarBotones()
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

    jugador = new Jugador(ui->graphicsView->scene());
    ui->graphicsView->scene()->addItem(jugador);
    timer->start(16);
}

void MainWindow::nivel2()
{
    interfazPrincipal->cargarEscenaNivel2();
    jugador = new Jugador(ui->graphicsView->scene());
    ui->graphicsView->scene()->addItem(jugador);
    //timer->start(16);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    jugador->keyPressEvent(event);
}















