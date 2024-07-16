#ifndef POINTMASSIF_H
#define POINTMASSIF_H

#include <QVector3D>
#include <QList>

class PointMassif
{
public:
    PointMassif();
    void tick(int temps);
    float masse() const;
    void setMasse(float newMasse);

    QVector3D pos() const;
    void setPos(const QVector3D &newPos);

    void clearForces();
    void addForce(const QVector3D &f);
    QVector3D vit() const;
    void setVit(const QVector3D &newVit);

    void setNom(const QString &newNom);

private:
    QString _nom;
    QVector3D _pos;
    QVector3D _vit;
    QList<QVector3D> _forces;
    float _masse;
};

#endif // POINTMASSIF_H
