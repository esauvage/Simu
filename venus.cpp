#include "venus.h"

Venus::Venus()
    :PointMassif()
{
    setNom("Venus");
    setMasse(4.8675e24);
    setPos(QVector3D(108943e6, 0, 0));
    setVit(QVector3D(0, 34.7895e3, 0));
}
