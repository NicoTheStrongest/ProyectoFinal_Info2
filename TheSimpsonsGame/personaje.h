#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include "sprites.h"
#include "fisicas.h"

class personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit personaje(QObject *parent = nullptr);
    personaje(Ui::MainWindow *ui);
signals:
private:
    Ui::MainWindow* vista;

};

#endif // PERSONAJE_H
