#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>


#include "menu.h"
#include "mapa.h"
#include "personaje.h"

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
    Menu* interfazPrincipal;
    short int nivel;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void renderEscena();
public slots:
    void nivel1();
    void nivel2();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
