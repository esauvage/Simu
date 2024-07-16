#include "terre.h"

Terre::Terre()
    :PointMassif()
{
    setNom("Terre");
    setMasse(5.9722e24);
    setPos(QVector3D(152097701e3, 0, 0));
    setVit(QVector3D(0, 29.291e3, 0));
}
