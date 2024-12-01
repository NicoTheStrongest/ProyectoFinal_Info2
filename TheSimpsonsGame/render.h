#ifndef RENDER_H
#define RENDER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QString>
#include "ui_mainwindow.h"  // Incluye el archivo de interfaz
#include "jugador.h"

class Jugador;

class Render : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Render(QObject *parent = nullptr);
    Render(Ui::MainWindow *ui);

    //METODOS
    void cargarEscenaNivel1();
    void añadirBasura();
    void cargarEscenaNivel2();
    void añadirPlataformas();
    void dibujarPared(int x, int y, int ancho, int alto, QColor color);
    void mostrarMensajeFinal(short int vida, QPoint posicion);
public slots:
    void volverAlMenuPrincipal();
private:
    //ATRIBUTOS
    Ui::MainWindow* vista;
    QLabel* puntaje;
    QLabel* vida;
    QGraphicsScene* escena;
    QGraphicsPixmapItem* fondo;
};

#endif // RENDER_H
