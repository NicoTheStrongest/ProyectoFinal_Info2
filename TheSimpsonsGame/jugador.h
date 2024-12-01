#ifndef JUGADOR_H
#define JUGADOR_H

#include <QApplication>
#include <QObject>
#include <Qpoint>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <String>
#include "personaje.h"
#include "fisicas.h"

using namespace std;

class Jugador : public personaje, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Jugador(QObject *parent = nullptr);
    Jugador(QGraphicsScene* escena, int nivel);

    //GETTERS
    QPoint getPosicion() const;
    short int getPuntos() const;
    short int getVida() const;
    bool getControl() const;
    int getNivelActual() const;

    //METODOS
    void saltar();
    void cargarPersonaje(QGraphicsScene *scene);
    void moverAdelante();
    void moverAtras();
    void moverArriba();
    void moverAbajo();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void keyPressEvent(QKeyEvent *event);
    void aumentarPuntos();
    void disminuirVida();
    bool finalizarNivel();
    void movimientoNivel2(QKeyEvent *event);
signals:
    void puntajeCambiado(short int nuevoPuntaje);
    void vidaCambio(short int nuevaVida);
public slots:
    void cambiarSprite();
    void aplicarGravedad();
private:
    //ATRIBUTOS
    QTimer* sprite;
    QTimer* mover;
    QPixmap* pixmap;
    QPoint posicion;
    string ultimaDireccionX;
    Fisicas objetoFisico;
    bool control, colision;
    double velocidadSalto;
    float filas, columnas, ancho, alto;
    short int direccionActual, velocidad, puntos, vida;
    int nivelActual;
};

#endif // JUGADOR_H
