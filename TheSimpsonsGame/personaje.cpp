#include "personaje.h"

personaje::personaje(QObject *parent)
    : QObject{parent}
{}

personaje::personaje(Ui::MainWindow *ui) : vista(ui)
{}
