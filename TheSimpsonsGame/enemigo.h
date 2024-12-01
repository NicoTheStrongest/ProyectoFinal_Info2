#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QApplication>
#include <Qpoint>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>

#include "personaje.h"
#include "fisicas.h"


class Enemigo : public personaje, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemigo(QObject *parent = nullptr);
    Enemigo(QPoint posicionInicial, int velocidad, int direccionActual, float columnaInicial, float fila, float ancho);

    //METODOS
    void moverArriba();
    void moverAbajo();
    void moverAdelante();
    void moverAtras();

    void cargarEnemigosNivel1(QGraphicsScene *scene);
    void cargarEnemigosNivel2(QGraphicsScene *scene);
    void cargarEnemigosNivel2Nico(QGraphicsScene *scene);
    void iniciarRotacion();
    void detenerRotacion();
    void cargarEnemigosNivel3(QGraphicsScene *scene);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public slots:
    void mover();
    void cambiarSprite();
    void movimientoSierra();
private:
    //ATRIBUTOS
    QPoint posicion;
    QTimer* timer;
    QTimer* moverSierra;
    QPointF posicionSierra, posicionSierra2;
    qreal rotacionSierra;
    QPixmap* sprite;
    QGraphicsPixmapItem *sierraItem;
    QGraphicsPixmapItem *sierra2Item;
    QVector<Enemigo*> enemigosNivel1;
    Fisicas objetoFisico;
    int velocidad, direccionActual;
    float columnaInicial, fila, ancho, alto, columna;
};

#endif // ENEMIGO_H
