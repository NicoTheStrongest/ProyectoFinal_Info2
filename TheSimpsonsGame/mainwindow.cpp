#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //LECTURA DE USUARIOS
    lectura(mapaUsuarios);

    //CONFIGURACION DE MENU PRINCIPAL (REDER PARA MANIPULACION DE ESCENARIOS)
    menuPrincipal = true;
    nivel = 0;
    interfazPrincipal = new Render(ui);
    conectarBotones();

    //TIMER PARA SEGUIR PERSONAJE
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkFinish()));

    //MONTAR ESCENA Y SETTEAR EL FOCUS
    ui->graphicsView->show();
    this->setFocusPolicy(Qt::StrongFocus);
}

MainWindow::~MainWindow()
{
    delete interfazPrincipal;
    delete ui;
    delete timer;
}

//-------------------METODOS--------------------------
void MainWindow::conectarBotones(){
    connect(ui->botonNivel1, &QPushButton::clicked, this, &MainWindow::nivel1);
    connect(ui->botonNivel2, &QPushButton::clicked, this, &MainWindow::nivel2);
    connect(ui->botonSalir, &QPushButton::clicked, this, [](){
        qDebug() << "Botón salir presionado";
        QApplication::quit();
    });
    connect(ui->botonAtras, &QPushButton::clicked, this, [this](){
        qDebug() << "Botón atras presionado";
        if(nivel == 2){
            this->enemigo2->detenerRotacion();
            this->enemigo3->detenerRotacion();
        }
        interfazPrincipal->volverAlMenuPrincipal();
        puntaje->setVisible(false);
        delete puntaje;
        puntaje = nullptr;
        vida->setVisible(false);
        delete vida;
        vida = nullptr;
    });
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
    if(enemigo2){
        delete enemigo2;
        enemigo2 = nullptr;
        qDebug() << "enemigo2 eliminado";
    }
    if(enemigo3){
        delete enemigo3;
        enemigo3 = nullptr;
        qDebug() << "enemigo3 eliminado";
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
                if(nivel == 2){
                    this->enemigo2->detenerRotacion();
                    this->enemigo3->detenerRotacion();
                }
                eliminarNivel();
                interfazPrincipal->volverAlMenuPrincipal();
            }
            menuPrincipal = true;
            event->accept();
        }
    }
    else if(!menuPrincipal) {
        if(this->nivel == 1){
            jugador->keyPressEvent(event);
            ui->graphicsView->centerOn(jugador);
        }
        if(this->nivel == 2){
            //qDebug() << event;
            jugador->movimientoNivel2(event);
            ui->graphicsView->centerOn(jugador);
        }
    }
}

void MainWindow::lectura(QMap<QString, QString> &usuarios){
    // Ruta del archivo
    QString nombreArchivo = "./../../usuarios/usuariosBase.txt";

    // Crear un objeto QFile con el nombre del archivo
    QFile archivo(nombreArchivo);

    // Abrir el archivo en modo de lectura
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << archivo.errorString();
        return;
    }

    // Crear un objeto QTextStream para leer el archivo
    QTextStream stream(&archivo);
    // Leer el archivo línea por línea
    while (!stream.atEnd()) {
        QString linea = stream.readLine();  // Lee una línea
        QString usuario = "";
        QString contra = "";
        bool usuarioListo = false;
        for(int i = 0; i < (int)linea.size(); i++){
            if(linea[i] != ',' && usuarioListo == false){usuario += linea[i];}
            else{usuarioListo = true;}
            if(usuarioListo == true && i != (int)linea.size()-1){contra += linea[i+1];}
        }
        usuarios[usuario] = contra;
    }
    // Cerrar el archivo
    archivo.close();
}

void MainWindow::escritura(const QMap<QString, QString> &usuarios) {
    // Ruta del archivo
    QString nombreArchivo = "./../../usuarios/usuariosBase.txt";

    // Crear un objeto QFile con el nombre del archivo
    QFile archivo(nombreArchivo);

    // Abrir el archivo en modo de escritura (sobrescribe el archivo si ya existe)
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << archivo.errorString();
        return;
    }

    // Crear un objeto QTextStream para escribir en el archivo
    QTextStream stream(&archivo);

    // Iterar sobre el QMap y escribir cada usuario y su contraseña
    QMapIterator<QString, QString> i(usuarios);
    while (i.hasNext()) {
        i.next();
        // Escribir el usuario y la contraseña, separados por una coma
        stream << i.key() << "," << i.value() << "\n";
    }

    // Cerrar el archivo
    archivo.close();
}

//-------------------SLOTS--------------------------
void MainWindow::checkFinish(){
    if(jugador->finalizarNivel()){
        timer->stop();
        interfazPrincipal->mostrarMensajeFinal(jugador->getVida(),jugador->getPosicion());
        menuPrincipal = true;
        return;
    }
    //ui->graphicsView->centerOn(jugador);
}

void MainWindow::actualizarPuntaje(short int nuevoPuntaje){
    puntaje->setText("PTS " + QString::number(nuevoPuntaje));
}

void MainWindow::actualizarVida(short int nuevaVida){
    vida->setText("LIFE " + QString::number(nuevaVida));
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

    enemigo = new Enemigo();
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

    ui->graphicsView->centerOn(jugador);

    timer->start(16);
    qDebug() << "timer iniciado (actualizacion de la vista)";
    qDebug() << "Nivel 1 cargado sin errores";
}

void MainWindow::nivel2()
{
    nivel = 2;
    interfazPrincipal->cargarEscenaNivel2();
    menuPrincipal = false;
    qDebug() << "Escena cargada";

    jugador = new Jugador(ui->graphicsView->scene(), nivel);
    ui->graphicsView->scene()->addItem(jugador);
    qDebug() << "jugador cargado";

    enemigo = new Enemigo(ui->graphicsView->scene());
    enemigo->cargarEnemigosNivel2(ui->graphicsView->scene());
    qDebug() << "enemigos cargados";

    enemigo2 = new Enemigo();
    enemigo2->cargarEnemigosSierra1(ui->graphicsView->scene(), 100, 370);
    enemigo2->iniciarRotacion();
    qDebug() << "sierra 1 cargado";
    enemigo3 = new Enemigo();
    enemigo3->cargarEnemigosSierra2(ui->graphicsView->scene(), 760, 230);
    enemigo3->iniciarRotacion();
    qDebug() << "sierra 2 cargado";

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

    ui->graphicsView->centerOn(jugador);

    timer->start(16);
    qDebug() << "timer iniciado (actualizacion de la vista)";
    qDebug() << "Nivel 2 cargado sin errores";
}

void MainWindow::on_ingresar_clicked()
{
    // Obtener los valores ingresados en los QLineEdits
    QString usuarioIngresado = ui->usuario->text();
    QString contraseñaIngresada = ui->contra->text();

    qDebug() << "Usuario: " << usuarioIngresado;
    qDebug() << "Contraseña: " << contraseñaIngresada;

    // Verificar si el usuario existe y la contraseña es correcta
    if (this->mapaUsuarios.contains(usuarioIngresado) && this->mapaUsuarios[usuarioIngresado] == contraseñaIngresada) {
        qDebug() << "Inicio de sesión exitoso";
        QMessageBox::information(this, "Éxito", "Inicio de sesión exitoso.");
        interfazPrincipal->cargarMenuNivel();
    } else {
        qDebug() << "Credenciales incorrectas";
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
    }
}














