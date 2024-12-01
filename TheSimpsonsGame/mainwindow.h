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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //METODOS
    void conectarBotones();
    void eliminarNivel();
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void actualizarVista();
    void actualizarPuntaje(short int nuevoPuntaje);
    void actualizarVida(short int nuevaVida);
    void nivel1();
    void nivel2();
private:
    //ATRIBUTOS
    Ui::MainWindow *ui;
    Jugador* jugador;
    Enemigo* enemigo;
    QLabel* puntaje;
    QLabel* vida;
    QTimer* timer;
    bool menuPrincipal;
    short int nivel;
};
#endif // MAINWINDOW_H
