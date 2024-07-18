#ifndef SOLIDEMASSIF_H
#define SOLIDEMASSIF_H

#include "pointmassif.h"
class SolideMassif : public PointMassif
{
public:
    SolideMassif();
    void tick(int temps);
    void clearPoints();
    void addPoint(const std::shared_ptr <PointMassif> &f);
    QList <PointMassif *> points() const override;
    void clearForces() override;

private:
    QList<std::shared_ptr<PointMassif> > _points;
};

#endif // SOLIDEMASSIF_H
