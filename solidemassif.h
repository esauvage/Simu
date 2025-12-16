#ifndef SOLIDEMASSIF_H
#define SOLIDEMASSIF_H

#include "pointMateriel.h"

class LienRessort;

class SolideMassif : public PointMateriel
{
public:
    SolideMassif();
    void tick(int temps) override;
    void clearPoints();
    void addPoint(const std::shared_ptr <PointMateriel> &f);
    QList <std::shared_ptr<PointMateriel> > points() override;
    void clearForces() override;

private:
    QList<std::shared_ptr<PointMateriel> > _points;
    QVector3D _momentCinetique;
    QVector3D _vitAngle;
};

#endif // SOLIDEMASSIF_H
