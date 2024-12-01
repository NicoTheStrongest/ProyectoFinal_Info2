#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    menuPrincipal = true;
    nivel = 0;
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(actualizarVista()));
    //Conectar botones y crear render para manipulacion de escenarios
    interfazPrincipal = new Render(ui);
    conectarBotones();
    //ui->graphicsView->setFocus();
    ui->graphicsView->show();
    //this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete interfazPrincipal;
    delete ui;
    delete timer;
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
        interfazPrincipal->mostrarMensajeFinal(jugador->getVida(),jugador->getPosicion());
        return;
    }
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
    connect(ui->botonAtras, &QPushButton::clicked, this, [this](){
        qDebug() << "Botón atras presionado";
        interfazPrincipal->volverAlMenuPrincipal();
        puntaje->setVisible(false);
        delete puntaje;
        puntaje = nullptr;
        vida->setVisible(false);
        delete vida;
        vida = nullptr;

    });
}

void MainWindow::nivel1()
{
    nivel = 1;
    interfazPrincipal->cargarEscenaNivel1();
    qDebug() << "Escena cargada";
    menuPrincipal = false;
    jugador = new Jugador(ui->graphicsView->scene(), nivel);
    ui->graphicsView->scene()->addItem(jugador);
    qDebug() << "jugador cargado";
    enemigo = new Enemigo(ui->graphicsView->scene());
    enemigo->cargarEnemigosNivel1(ui->graphicsView->scene());
    qDebug() << "enemigos cargados";
    puntaje = new QLabel("PTS 0", this);
    puntaje->setGeometry(100, 90, 100, 30);
    puntaje->show();
    qDebug() << "puntaje cargado";
    vida = new QLabel("LIFE 100", this);
    vida->setGeometry(358, 90, 100, 30);
    vida->show();
    qDebug() << "vida cargada";
    connect(jugador, SIGNAL(puntajeCambiado(short)), this, SLOT(actualizarPuntaje(short)));
    connect(jugador, SIGNAL(vidaCambio(short)), this, SLOT(actualizarVida(short)));
    timer->start(16);
    qDebug() << "timer iniciado";
    qDebug() << "Nivel 1 cargado sin errores";
}

void MainWindow::nivel2()
{
    nivel = 2;
    interfazPrincipal->cargarEscenaNivel2();
    qDebug() << "Escena cargada";
    menuPrincipal = false;
    jugador = new Jugador(ui->graphicsView->scene(), nivel);
    ui->graphicsView->scene()->addItem(jugador);
    qDebug() << "Jugador cargado";
    enemigo = new Enemigo(ui->graphicsView->scene());
    enemigo->cargarEnemigosNivel2(ui->graphicsView->scene());
    qDebug() << "enemigos cargados";
    puntaje = new QLabel("PTS 0", this);
    puntaje->setGeometry(100, 90, 100, 30);
    puntaje->show();
    qDebug() << "puntaje cargado";
    vida = new QLabel("LIFE 100", this);
    vida->setGeometry(358, 90, 100, 30);
    vida->show();
    qDebug() << "vida cargada";
    connect(jugador, SIGNAL(puntajeCambiado(short)), this, SLOT(actualizarPuntaje(short)));
    connect(jugador, SIGNAL(vidaCambio(short)), this, SLOT(actualizarVida(short)));
    timer->start(16);
    qDebug() << "timer iniciado";
    qDebug() << "Nivel 2 cargado sin errores";
}

void MainWindow::eliminarNivel(){
    qDebug() << "liberando memoria del nivel";
    if(jugador){
        delete jugador;
        jugador = nullptr;
        qDebug() << "jugador eliminado";
    }
    if(enemigo){
        delete enemigo;
        enemigo = nullptr;
        qDebug() << "enemigo eliminado";
    }
    if(puntaje){
        puntaje->setVisible(false);
        delete puntaje;
        puntaje = nullptr;
        qDebug() << "puntaje eliminado";
    }
    if(vida){
        vida->setVisible(false);
        delete vida;
        vida = nullptr;
        qDebug() << "vida eliminado";
    }
    if(ui->graphicsView->scene()){
        ui->graphicsView->scene()->clear();
        qDebug() << "escena eliminado";
    }
    if(timer->isActive()){
        timer->stop();
    }

    qDebug() << "Nivel liberado.";
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape){
        qDebug() <<"tecla presionada desde main";
        if(!menuPrincipal){
            //Aca se puede poner tambien el menu de opciones para volver o continuar
            qDebug() << "Se presiono ESC. volviendo al menu principal";
            if(nivel == 1){
                eliminarNivel();
                interfazPrincipal->volverAlMenuPrincipal();
            }
            else{
                eliminarNivel();
                interfazPrincipal->volverAlMenuPrincipal();
            }
            menuPrincipal = true;
        }
    }
    else {
        if(this->nivel == 1){
            jugador->keyPressEvent(event);
            qDebug() << "hola";
        }
        if(this->nivel == 2){jugador->movimientoNivel2(event);}
    }
}















