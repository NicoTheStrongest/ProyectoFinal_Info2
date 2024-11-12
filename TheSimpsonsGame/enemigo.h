#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include "personaje.h"


class enemigo : public personaje
{
    Q_OBJECT
public:
    explicit enemigo(QObject *parent = nullptr);

signals:
};

#endif // ENEMIGO_H
