#ifndef SPRITES_H
#define SPRITES_H

#include <QObject>
#include <QPixmap>
#include <QVector>
#include <QString>
#include <QGraphicsPixmapItem>

class sprites : public QObject
{
    Q_OBJECT
public:
    explicit sprites(QObject *parent = nullptr);
    //sprites(const QString& rutaImagen, int numCuadros = 1, QColor colorTransparente = QColor(0, 255, 0));
    //QGraphicsPixmapItem* obtenerCuadro(int indice);
    //void siguienteCuadro();
signals:
private:
    //QVector<QPixmap> cuadros;  // Contiene cada cuadro del sprite (animación)
    //int indiceCuadroActual;    // Índice del cuadro actual
};

#endif // SPRITES_H
