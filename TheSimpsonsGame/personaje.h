#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"
#include "fisicas.h"

class personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit personaje(QObject *parent = nullptr);

signals:
};

#endif // PERSONAJE_H
