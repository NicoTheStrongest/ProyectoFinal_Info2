#ifndef FISICAS_H
#define FISICAS_H

#include <QObject>
#include <QPoint>
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>
#include <string>
#include <QGraphicsPixmapItem>
#include <QtMath>

using namespace std;

class Fisicas : public QObject
{
    Q_OBJECT
public:
    explicit Fisicas(QObject *parent = nullptr);

    //SETTERS
    void setTiempo(double newTiempo);

    //METODOS
    void aplicarGravedad(QPoint &posicion, int velocidadDefecto, string ultimaDireccionx);
    void inicializarMovimientoCircular(qreal xCentro, qreal yCentro, qreal radio,
                                            qreal velocidadAngular, qreal velocidadRotacion,
                                            int X, int Y);
    void aplicarMovimientocircular(QPointF& posicion, qreal &rotacionSierra);
private:
    //ATRIBUTOS PARA GRAVEDAD
    float gravedad, tiempo, velocidadY;

    //ATRIBUTOS PARA MOVIMIENTO CIRCULAR
    QPointF centro;
    qreal radio, anguloActual, velocidadAngular, velocidadRotacion;
    int desplazamientoX, desplazamientoY;
};

#endif // FISICAS_H
