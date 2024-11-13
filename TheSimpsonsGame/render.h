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

    QGraphicsScene* escena;
    QGraphicsPixmapItem* fondo;

    int elegirOpcion();
    void cargarEscenaNivel1();
    void añadirBasura();
    void añadirEnemigos();
    void cargarEscenaNivel2();
signals:
private:
    Ui::MainWindow* vista;
};

#endif // RENDER_H
