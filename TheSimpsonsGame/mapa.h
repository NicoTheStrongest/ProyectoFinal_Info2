#ifndef MAPA_H
#define MAPA_H

#include <QObject>


class mapa : public QObject
{
    Q_OBJECT
public:
    explicit mapa(QObject *parent = nullptr);

signals:
};

#endif // MAPA_H
