#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QMainWindow>
#include <QDebug>

#include "ui_mainwindow.h"  // Incluye el archivo de interfaz


class Menu : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Menu(QObject *parent = nullptr);
    Menu(Ui::MainWindow *ui);

    QGraphicsScene* escena;
    QGraphicsPixmapItem* menu;

    int elegirOpcion();
    void conectarBotones();
signals:
private:
    Ui::MainWindow* vista;
public slots:
    void nivel1();
    void nivel2();
    void salir();
};

#endif // MENU_H
