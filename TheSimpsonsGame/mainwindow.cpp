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

void MainWindow::actualizarPuntaje(short int nuevoPuntaje){
    puntaje->setText("PTS " + QString::number(nuevoPuntaje));
}

void MainWindow::actualizarVida(short int nuevaVida){
    vida->setText("LIFE " + QString::number(nuevaVida));
}

void MainWindow::actualizarVista(){
    if(jugador->finalizarNivel()){
        timer->stop();
        jugador->parar();
        enemigo->parar();
        interfazPrincipal->mostrarMensajeFinal(jugador->getVida(),jugador->getPosicion());
        return;
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
    enemigo = new Enemigo(ui->graphicsView->scene());
    enemigo->cargarEnemigosNivel1(ui->graphicsView->scene());
    puntaje = new QLabel("PTS 0", this);
    puntaje->setGeometry(100, 90, 100, 30);
    puntaje->show();
    vida = new QLabel("LIFE 100", this);
    vida->setGeometry(358, 90, 100, 30);
    vida->show();
    connect(jugador, SIGNAL(puntajeCambiado(short)), this, SLOT(actualizarPuntaje(short)));
    connect(jugador, SIGNAL(vidaCambio(short)), this, SLOT(actualizarVida(short)));
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















