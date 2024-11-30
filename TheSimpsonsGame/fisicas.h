#ifndef FISICAS_H
#define FISICAS_H

#include <QObject>
#include <Qpoint>
#include <QGraphicsItem>
#include <QDebug>
#include <QTimer>

class Fisicas : public QObject
{
    Q_OBJECT
public:
    explicit Fisicas(QObject *parent = nullptr);
    void aplicarGravedad(QPoint &posicion, int velocidadDefecto);
private:
    float gravedad, velocidad;
};

#endif // FISICAS_H
