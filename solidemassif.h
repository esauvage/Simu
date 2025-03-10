#ifndef SOLIDEMASSIF_H
#define SOLIDEMASSIF_H

#include "pointmassif.h"

class LienRessort;

class SolideMassif : public PointMassif
{
public:
    SolideMassif();
    void tick(int temps) override;
    void clearPoints();
    void addPoint(const std::shared_ptr <PointMassif> &f);
    QList <std::shared_ptr<PointMassif> > points() override;
    void clearForces() override;

private:
    QList<std::shared_ptr<PointMassif> > _points;
    QVector3D _momentCinetique;
    QVector3D _vitAngle;
};

#endif // SOLIDEMASSIF_H
