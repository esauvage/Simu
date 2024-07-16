#include "mercure.h"

Mercure::Mercure()
    :PointMassif()
{
    setNom("Mercure");
    setMasse(3.3011e23);
    setPos(QVector3D(69816900e3, 0, 0));
    setVit(QVector3D(0, 38.86e3, 0));
}
