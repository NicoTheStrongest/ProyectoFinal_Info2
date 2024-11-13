#include "sprites.h"

sprites::sprites(QObject *parent)
    : QObject{parent}
{}

/*
Posibles para clase sprites

sprites::sprites(const QString& rutaImagen, int numCuadros, QColor colorTransparente)
    : indiceCuadroActual(0) {
    QPixmap spriteCompleto(rutaImagen);

    // Divide el sprite en cuadros si es una animación en una sola imagen
    int anchoCuadro = spriteCompleto.width() / numCuadros;
    for (int i = 0; i < numCuadros; ++i) {
        QPixmap cuadro = spriteCompleto.copy(i * anchoCuadro, 0, anchoCuadro, spriteCompleto.height());
        cuadro.setMask(cuadro.createMaskFromColor(colorTransparente.rgb(), Qt::MaskInColor));
        cuadros.append(cuadro);
    }
}

QGraphicsPixmapItem* sprites::obtenerCuadro(int indice) {
    if (indice >= 0 && indice < cuadros.size()) {
        return new QGraphicsPixmapItem(cuadros[indice]);
    }
    return nullptr;
}

void sprites::siguienteCuadro() {
    indiceCuadroActual = (indiceCuadroActual + 1) % cuadros.size();
}
*/

