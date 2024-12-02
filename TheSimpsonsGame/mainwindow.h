#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include "personaje.h"
#include "render.h"
#include "enemigo.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //METODOS
    void conectarBotones();
    void eliminarNivel();
    void keyPressEvent(QKeyEvent *event) override;
    void lectura(QMap<QString, QString> &usuarios);
    void escritura(const QMap<QString, QString> &usuarios);
public slots:
    void checkFinish();
    void actualizarPuntaje(short int nuevoPuntaje);
    void actualizarVida(short int nuevaVida);
    void nivel1();
    void nivel2();
private slots:
    void on_ingresar_clicked();
private:
    //ATRIBUTOS
    Ui::MainWindow *ui;
    Render* interfazPrincipal;
    QGraphicsScene* scene;
    Jugador* jugador;
    Enemigo* enemigo;
    Enemigo* enemigo2;
    Enemigo* enemigo3;
    QLabel* puntaje;
    QLabel* vida;
    QTimer* timer;
    QMap<QString, QString> mapaUsuarios;
    bool menuPrincipal;
    short int nivel;
};
#endif // MAINWINDOW_H
