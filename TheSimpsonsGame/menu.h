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
    void cargarEscenaNivel1();
    void cargarEscenaNivel2();
signals:
private:
    Ui::MainWindow* vista;
public slots:
};

#endif // MENU_H
