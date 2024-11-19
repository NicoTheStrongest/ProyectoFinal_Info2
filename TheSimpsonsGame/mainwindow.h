#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>

#include "personaje.h"
#include "render.h"
#include "enemigo.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsScene* scene;
    Render* interfazPrincipal;
    short int nivel;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void conectarBotones();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void actualizarVista();
    void nivel1();
    void nivel2();
private:
    Ui::MainWindow *ui;
    Jugador* jugador;
    QTimer* timer;
};
#endif // MAINWINDOW_H
