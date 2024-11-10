#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include "personaje.h"


class jugador : public QObject, public personaje
{
    Q_OBJECT
public:
    explicit jugador(QObject *parent = nullptr);

signals:
};

#endif // JUGADOR_H
