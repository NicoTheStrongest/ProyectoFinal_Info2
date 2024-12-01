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
    Enemigo(QPoint posicionInicial, int velocidad, int direccionActual, float columnaInicial, float fila, float ancho, float alto, short int nivel);
    QPoint getPosicion() const;
    void moverArriba();
    void moverAbajo();
    void moverAdelante();
    void moverAtras();

    void cargarEnemigosNivel1(QGraphicsScene *scene);
    void cargarEnemigosNivel2(QGraphicsScene *scene);
    void cargarSpriteNivel(short int nivel);
    void cargarEnemigosSierra1(QGraphicsScene *scene, int posX, int posY);
    void cargarEnemigosSierra2(QGraphicsScene *scene, int posX, int posY);
    void iniciarRotacion();
    void detenerRotacion();
    void cargarEnemigosNivel3(QGraphicsScene *scene);
    
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public slots:
    void moverNivel1();
    void moverNivel2();
    void moverAntorchas();
    void cambiarSprite();
    void lanzarAntorcha();
    void movimientoSierra();
private:
    //ATRIBUTOS
    QPoint posicion;
    QTimer* timer;
    QTimer* timer2;
    QTimer* timer3;
    QTimer* lanzamiento;
    QPixmap* sprite;
    Fisicas objetoFisico;
    QList<QGraphicsPixmapItem*> antorchas;
    int velocidad, direccionActual, limiteIzquierda, limiteDerecha;
    short int nivel;
    float columnaInicial, fila, ancho, alto, columna;
    QTimer* moverSierra;
    QPointF posicionSierra, posicionSierra2;
    qreal rotacionSierra;
    QGraphicsPixmapItem *sierraItem;
    QGraphicsPixmapItem *sierra2Item;
    //QVector<Enemigo*> enemigosNivel1;
};

#endif // ENEMIGO_H
