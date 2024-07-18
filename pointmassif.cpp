#include "pointmassif.h"

#include <QDebug>

using namespace std;

PointMassif::PointMassif()
    :_pos(0, 0, 0), _vit(0, 0, 0), _masse(0), _parent(nullptr)
{

}

void PointMassif::tick(int temps)
{
    QVector3D a;
    if (_masse)
    {
        a = force()/_masse;
    }
    _vit += a * temps;
    _pos += _vit * temps;
    qDebug() << _nom << "Position : " << _pos << "Vitesse : " << _vit << "Accélération :" << a << a.length();
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
    return _parent ? _pos + _parent->pos() : _pos;
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

QVector3D PointMassif::force() const
{
    QVector3D r;
    for (const auto & f : _forces)
    {
        r += f;
    }
    return r;
}

QVector3D PointMassif::vit() const
{
    return _parent ? _parent->vit() + _vit : _vit;
}

void PointMassif::setVit(const QVector3D &newVit)
{
    _vit = newVit;
}

QString PointMassif::nom() const
{
    return _nom;
}

void PointMassif::setNom(const QString &newNom)
{
    _nom = newNom;
}

PointMassif *PointMassif::parent() const
{
    return _parent;
}

void PointMassif::setParent(PointMassif *newParent)
{
    _parent = newParent;
}

QList<PointMassif *> PointMassif::points() const
{
    QList<PointMassif *>r;
    r << const_cast<PointMassif *>(this);
    return r;
}
