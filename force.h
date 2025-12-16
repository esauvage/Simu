#ifndef FORCE_H
#define FORCE_H

#include <QVector3D>

class PointMateriel;

class Force
{
public:
    Force(std::shared_ptr<PointMateriel>source, QVector3D intensite);
    QVector3D intensite() const;

private:
    std::shared_ptr<PointMateriel>_source;
    QVector3D _intensite;
};

#endif // FORCE_H
