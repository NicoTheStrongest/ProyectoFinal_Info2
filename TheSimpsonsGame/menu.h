#ifndef MENU_H
#define MENU_H

#include <QObject>

class Menu : public QObject, public
{
    Q_OBJECT
public:
    explicit Menu(QObject *parent = nullptr);

signals:
};

#endif // MENU_H
