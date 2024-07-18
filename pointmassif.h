#ifndef POINTMASSIF_H
#define POINTMASSIF_H

#include <QVector3D>
#include <QList>

class PointMassif
{
public:
    PointMassif();
    virtual void tick(int temps);
    float masse() const;
    void setMasse(float newMasse);

    QVector3D pos() const;
    void setPos(const QVector3D &newPos);

    virtual void clearForces();
    void addForce(const QVector3D &f);
    QVector3D force() const;
    QVector3D vit() const;
    void setVit(const QVector3D &newVit);

    QString nom() const;
    void setNom(const QString &newNom);

    PointMassif *parent() const;
    void setParent(PointMassif *newParent);
    virtual QList <PointMassif *> points() const;

private:
    QString _nom;
    QVector3D _pos;
    QVector3D _vit;
    QList<QVector3D> _forces;
    float _masse;
    PointMassif * _parent;
};

#endif // POINTMASSIF_H
