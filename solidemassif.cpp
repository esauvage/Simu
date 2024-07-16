#include "solidemassif.h"

SolideMassif::SolideMassif() {}

void SolideMassif::tick(int temps)
{
    QVector3D centre;
    for (auto & p : _points)
    {
        centre += p.pos() * p.masse();
    }
    QVector3D moment;
    for (auto & p : _points)
    {
        moment += QVector3D::crossProduct((p.pos() - centre), p.a());
    }
    qDebug() << _nom << "Position : " << _pos << "Vitesse : " << _vit;
}
