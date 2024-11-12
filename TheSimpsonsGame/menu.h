#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include "ui_mainwindow.h"  // Incluye el archivo de interfaz
#include "jugador.h"

class Jugador;

class Menu : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Menu(QObject *parent = nullptr);
    Menu(Ui::MainWindow *ui);

    QGraphicsScene* escena;
    QGraphicsPixmapItem* menu;

    int elegirOpcion();
    void cargarEscenaNivel1();
    void cargarEscenaNivel2();

    void conectarBotones();
    void cargarPersonaje(QGraphicsScene *scene);
    void actualizarJuego();
    void keyPressEvent(QKeyEvent *event);

signals:

private:
    Ui::MainWindow* vista;
    Jugador* jugador;
    QTimer* timer;
public slots:
};

#endif // MENU_H
