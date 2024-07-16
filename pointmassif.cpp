#include "pointmassif.h"

#include <QDebug>

PointMassif::PointMassif()
    :_pos(0, 0, 0), _vit(0, 0, 0), _masse(0)
{

}

void PointMassif::tick(int temps)
{
    QVector3D a;
    if (_masse)
    {
        for (const auto & f : _forces)
        {
            a += f;
        }
        a /= _masse;
    }
    _vit += a * temps;
    _pos += _vit * temps;
    qDebug() << _nom << "Position : " << _pos << "Vitesse : " << _vit;
}

float PointMassif::masse() const
{
    return _masse;
}

void PointMassif::setMasse(float newMasse)
{
    _masse = newMasse;
}

QVector3D PointMassif::pos() const
{
    return _pos;
}

void PointMassif::setPos(const QVector3D &newPos)
{
    _pos = newPos;
}

void PointMassif::clearForces()
{
    _forces.clear();
}

void PointMassif::addForce(const QVector3D &f)
{
    _forces << f;
}

QVector3D PointMassif::vit() const
{
    return _vit;
}

void PointMassif::setVit(const QVector3D &newVit)
{
    _vit = newVit;
}

void PointMassif::setNom(const QString &newNom)
{
    _nom = newNom;
}
